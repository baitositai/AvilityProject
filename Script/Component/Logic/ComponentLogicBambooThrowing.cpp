#include <random>
#include <cmath>
#include "../../Manager/Game/CollisionManager.h"
#include "../../Manager/Game/GimmickManager.h"
#include "../../Collider/ColliderCircle.h"
#include "../../Object/Common/Animation.h"
#include "../../Object/Character/Enemy/EnemyPanda.h"
#include "../../Utility/UtilityCommon.h"
#include "ComponentLogicBambooThrowing.h"

ComponentLogicBambooThrowing::ComponentLogicBambooThrowing(EnemyPanda& owner) :
	ComponentLogicBase(owner),
	owner_(owner),
	parameter_(owner.GetParameter())
{
	// シードを用意してエンジンに渡しておく
	std::random_device seedGen;
	randomCountEngine_.seed(seedGen());

	// 変数の初期化
	bambooThrowCount_ = -1;
	isAttack_ = false;
	attackPos_ = {};
	attackCollider_ = nullptr;
	state_ = STATE::THROW;

	// 状態遷移処理のマップを初期化
	changeStateMap_.emplace(STATE::ANIMATION, std::bind(&ComponentLogicBambooThrowing::ChangeStateAnimation, this));
	changeStateMap_.emplace(STATE::THROW, std::bind(&ComponentLogicBambooThrowing::ChangeStateThrow, this));
}

ComponentLogicBambooThrowing::~ComponentLogicBambooThrowing()
{
}

void ComponentLogicBambooThrowing::Create()
{
	// 攻撃用コライダーの登録
	attackCollider_ = std::make_shared<ColliderCircle>(owner_, parameter_.attackCollisionTag_, attackPos_, parameter_.defaultAttackRadius_);
	attackCollider_->SetIsActive(false);
	collisionManager_.Add(attackCollider_);
}

void ComponentLogicBambooThrowing::Init()
{
	ComponentLogicBase::Init();
	ChangeState(STATE::THROW);
	bambooThrowCount_ = UtilityCommon::GetRandomCount(5, 3);
}

void ComponentLogicBambooThrowing::Update()
{
	update_();
}

void ComponentLogicBambooThrowing::Remove()
{
	if (attackCollider_)
	{
		attackCollider_->Delete();
		attackCollider_ = nullptr;
	}
}

void ComponentLogicBambooThrowing::UpdateAnimation()
{
	Animation& animation = owner_.GetAnimation();
	if (animation.GetAnimationIndex() >= owner_.GetParameter().defaultAttackStartFrame_ && !isAttack_)
	{
		// 攻撃のコライダー設定
		attackCollider_->SetIsActive(true);

		// 竹の作成
		

		// 攻撃判定
		isAttack_ = true;
	}

	// 攻撃位置を追従
	if (attackCollider_->IsActive())
	{
		Vector2F dir = Vector2F::MulVector2FFloat(parameter_.GetFront(), parameter_.scale_);
		attackPos_ = Vector2F::AddVector2F(parameter_.pos_, Vector2F::MulVector2FFloat(dir, parameter_.defaultAttackDistance_));
	}

	// アニメーションが終わった場合
	if (!animation.IsPlay())
	{
		// コライダーの判定を無効
		attackCollider_->SetIsActive(false);

		// まだ投げる回数が残っている場合
		if (bambooThrowCount_ > 0)
		{
			bambooThrowCount_--;
			ChangeState(STATE::THROW);
		}
		else
		{
			isEnd_ = true;
		}
	}
}

void ComponentLogicBambooThrowing::UpdateThrow()
{
	ChangeState(STATE::ANIMATION);
}

void ComponentLogicBambooThrowing::ChangeState(const STATE state)
{
	state_ = state;
	changeStateMap_[state_]();
}

void ComponentLogicBambooThrowing::ChangeStateThrow()
{
	update_ = std::bind(&ComponentLogicBambooThrowing::UpdateThrow, this);

	// 攻撃判定初期化
	isAttack_ = false;
}

void ComponentLogicBambooThrowing::CreateBamboo()
{
	// 所有者の前方向取得
	Vector2F fornt = parameter_.GetFront();

	// 竹の生成位置を決定
	Vector2F localPos = Vector2F::MulVector2FFloat(fornt, 30.0f);
	Vector2F pos = Vector2F::AddVector2F(parameter_.pos_, localPos);

	// 竹の移動方向を設定
	Vector2F ownerDir = parameter_.GetFront();
	Vector2F moveDir = ownerDir;

	// ぶれさせる最大角度（例：15度をラジアンに変換）
	const float MAX_ANGLE_DEGREE = 15.0f;
	const float MAX_ANGLE_RADIAN = MAX_ANGLE_DEGREE * (3.14159265f / 180.0f);

	// -MAX_ANGLE_RADIAN から +MAX_ANGLE_RADIAN までの範囲の乱数
	std::uniform_real_distribution<float> convertAngle(-MAX_ANGLE_RADIAN, MAX_ANGLE_RADIAN);
	float randomAngle = convertAngle(randomCountEngine_);

	// ベクトルを回転（回転行列の計算）
	float sinAngle = std::sin(randomAngle);
	float cosAngle = std::cos(randomAngle);

	float rotatedX = moveDir.x * cosAngle - moveDir.y * sinAngle;
	float rotatedY = moveDir.x * sinAngle + moveDir.y * cosAngle;

	moveDir.x = rotatedX;
	moveDir.y = rotatedY;

	// 竹生成
	gimmickManager_.Create(GimmickTypes::TYPE::BAMBOO, pos, moveDir);
}

void ComponentLogicBambooThrowing::ChangeStateAnimation()
{
	update_ = std::bind(&ComponentLogicBambooThrowing::UpdateAnimation, this);

	// アニメーションの指定
	owner_.GetAnimation().Play(Animation::TYPE::ATTACK, false);
}