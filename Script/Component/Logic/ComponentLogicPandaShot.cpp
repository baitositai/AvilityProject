#include <DxLib.h>
#include "../../Application.h"
#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Game/CollisionManager.h"
#include "../../Manager/Game/GimmickManager.h"
#include "../../Collider/ColliderBox.h"
#include "../../Object/Common/Animation.h"
#include "../../Object/Character/Enemy/EnemyPanda.h"
#include "../../Utility/UtilityCommon.h"
#include "ComponentLogicPandaShot.h"

ComponentLogicPandaShot::ComponentLogicPandaShot(EnemyPanda& owner) :
	ComponentLogicBase(owner),
	owner_(owner),
	parameter_(owner.GetParameter())
{
	reflectCount_ = -1;
	timer_ = 0.0f;
	state_ = STATE::START;
	moveStartPos_ = {};
	moveEndPos_ = {};
	changeStateMap_.emplace(STATE::START, std::bind(&ComponentLogicPandaShot::ChangeStateStart, this));
	changeStateMap_.emplace(STATE::READY, std::bind(&ComponentLogicPandaShot::ChangeStateReady, this));
	changeStateMap_.emplace(STATE::CHARGE, std::bind(&ComponentLogicPandaShot::ChangeStateCharge, this));
	changeStateMap_.emplace(STATE::SHOT, std::bind(&ComponentLogicPandaShot::ChangeStateShot, this));
}

ComponentLogicPandaShot::~ComponentLogicPandaShot()
{
}

void ComponentLogicPandaShot::Create()
{
	// コライダーを複製して攻撃コライダーとして登録
	attackCollider_ = owner_.CreateColliderClone();
	attackCollider_->ChangeTag(CollisionTags::TAG::ENEMY_ATTACK_NORMAL);
	attackCollider_->SetIsActive(false);
	collisionManager_.Add(attackCollider_);

	// 初期化処理
	Init();
}

void ComponentLogicPandaShot::Init()
{
	ComponentLogicBase::Init();
	ChangeState(STATE::START);
}

void ComponentLogicPandaShot::Update()
{
	update_();
}

void ComponentLogicPandaShot::Remove()
{
	if (attackCollider_)
	{
		attackCollider_->Delete();
		attackCollider_ = nullptr;
	}
}

void ComponentLogicPandaShot::AttackReset()
{
	attackCollider_->SetIsActive(false);
}

void ComponentLogicPandaShot::UpdateStart()
{
	// 体力が半分以下の場合
	if (parameter_.hpMax_ / 2 > parameter_.hp_)
	{
		// 状態遷移
		ChangeState(STATE::READY);
	}
	else
	{
		// 終了判定
		isEnd_ = true;
	}
}

void ComponentLogicPandaShot::UpdateReady()
{	
	constexpr float ARRIVE_RANGE = 10.0f;
	constexpr float ARRIVE_TIME = 1.0f;

	// 到着判定
	if (UtilityCommon::IsArrived(parameter_.pos_, moveEndPos_, ARRIVE_RANGE) &&
		timer_ > ARRIVE_TIME)
	{
		ChangeState(STATE::CHARGE);
		return;
	}

	// 移動量の更新
	timer_ += sceneManager_.GetDeltaTime();
	parameter_.pos_.x = UtilityCommon::EaseOutQuad(timer_, ARRIVE_TIME, moveStartPos_.x, moveEndPos_.x);
	parameter_.pos_.y = UtilityCommon::EaseOutQuad(timer_, ARRIVE_TIME, moveStartPos_.y, moveEndPos_.y);
}

void ComponentLogicPandaShot::UpdateCharge()
{
	timer_ -= sceneManager_.GetDeltaTime();
	if (timer_ < 0.0f)
	{
		ChangeState(STATE::SHOT);
	}
}

void ComponentLogicPandaShot::UpdateShot()
{
	// 移動処理
	parameter_.moveAmount_ = Vector2F::MulVector2FFloat(moveDir_, 10.0f);

	// 角度を決める
	float targetAngle = std::atan2f(moveDir_.y, moveDir_.x);
	parameter_.angle_ = targetAngle - (DX_PI_F / 2.0f);

	// 移動方向に応じて反対にする
	parameter_.direction_ = moveDir_.x > 0 ? false : true;

	// 各軸の衝突判定
	ProcessCollision(true);
	ProcessCollision(false);
}

void ComponentLogicPandaShot::ChangeState(const STATE state)
{
	state_ = state;
	changeStateMap_[state_]();
}

void ComponentLogicPandaShot::ChangeStateStart()
{
	update_ = std::bind(&ComponentLogicPandaShot::UpdateStart, this);

	// 待機アニメーション
	owner_.GetAnimation().Play(Animation::TYPE::IDLE);
}

void ComponentLogicPandaShot::ChangeStateReady()
{
	update_ = std::bind(&ComponentLogicPandaShot::UpdateReady, this);
	
	// タイマー初期化
	timer_ = 0.0f;

	// 重力オフ
	owner_.SetComponentActive("gravity", false);

	// 開始位置を指定
	moveStartPos_ = parameter_.pos_;

	// 終了位置を指定
	moveEndPos_ = { (float)Application::SCREEN_HALF_X, (float)Application::SCREEN_HALF_Y };
}

void ComponentLogicPandaShot::ChangeStateCharge()
{
	update_ = std::bind(&ComponentLogicPandaShot::UpdateCharge, this);

	// チャージタイム設定
	timer_ = 5.0f;
}

void ComponentLogicPandaShot::ChangeStateShot()
{
	update_ = std::bind(&ComponentLogicPandaShot::UpdateShot, this);

	// 自身の当たり判定を無効
	owner_.SetColliderActive(false);

	// 攻撃判定を有効
	attackCollider_->SetIsActive(true);

	// 反射回数初期化
	reflectCount_ = 0;

	// 飛ぶ方向をランダムで決定
	constexpr int ANGLES_NUM = 4;
	const std::array<float, ANGLES_NUM> ANGLES =
	{
		DX_PI_F * 0.25f, //  45度
		DX_PI_F * 0.75f, // 135度
		DX_PI_F * 1.25f, // 225度
		DX_PI_F * 1.75f  // 315度
	};

	// ランダムに選ばれた角度を取得
	int randomIndex = GetRand(ANGLES_NUM - 1);
	float angle = ANGLES[randomIndex];

	// 角度から単位ベクトルを計算
	moveDir_.x = std::cos(angle);
	moveDir_.y = std::sin(angle);
}

void ComponentLogicPandaShot::ProcessCollision(bool isXAxis)
{
	float& moveVal = isXAxis ? parameter_.moveAmount_.x : parameter_.moveAmount_.y;
	if (moveVal == 0.0f)
	{
		return;
	}

	float& currentPos = isXAxis ? parameter_.pos_.x : parameter_.pos_.y;

	float move = moveVal;
	float maxStep = 8.0f;
	int step = static_cast<int>(std::ceil(std::abs(move) / maxStep));
	if (step <= 0)
	{
		step = 1;
	}
	float stepMove = move / step;

	for (int i = 0; i < step; i++)
	{
		currentPos += stepMove;

		CollisionManager::CollisionCheckParam checkParameter;
		checkParameter.pos = parameter_.pos_.ToVector2();
		checkParameter.size = parameter_.hitSize_;
		checkParameter.isXAxis = isXAxis;
		checkParameter.stepMove = stepMove;

		CollisionManager::CollisionResult result = CollisionManager::GetInstance().CheckStageCollision(checkParameter);

		if (result.isHit)
		{
			// 1個戻す
			currentPos -= stepMove;

			CheckGroundStatus(stepMove, isXAxis);

			// 反射ベクトル計算（共通化した法線を使用）
			Vector2F reflectDir = UtilityCommon::Reflect(moveDir_, result.normal);
			moveDir_ = reflectDir;

			// 反射回数追加
			reflectCount_++;

			// 一定回数反射したら
			if (reflectCount_ > 12)
			{
				ShotEnd();
				return;
			}

			moveVal = 0.0f;
		}
	}
}

void ComponentLogicPandaShot::CheckGroundStatus(float moveVal, bool isXAxis)
{
	bool isGround = false;
	if (isXAxis)
	{
		if ((moveVal > 0.0f && parameter_.gravityDir_ == ParameterActor::DIR::RIGHT) ||
			(moveVal < 0.0f && parameter_.gravityDir_ == ParameterActor::DIR::LEFT)) isGround = true;
	}
	else
	{
		if ((moveVal > 0.0f && parameter_.gravityDir_ == ParameterActor::DIR::DOWN) ||
			(moveVal < 0.0f && parameter_.gravityDir_ == ParameterActor::DIR::UP)) isGround = true;
	}

	if (isGround) parameter_.isGround_ = true;
}

void ComponentLogicPandaShot::ShotEnd()
{
	isEnd_ = true;
	owner_.SetComponentActive("gravity", true);
	parameter_.angle_ = 0.0f;	
	owner_.SetColliderActive(true);
	attackCollider_->SetIsActive(false);
}