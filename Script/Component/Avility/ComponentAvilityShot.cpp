#include <tgmath.h>
#include "../../Utility/UtilityCommon.h"
#include "../../Common/Vector2F.h"
#include "../../Manager/Common/InputManager.h"
#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Common/SpriteEffectManager.h"
#include "../../Manager/Common/Camera.h"
#include "../../Manager/Common/SoundManager.h"
#include "../../Manager/Game/CollisionManager.h"
#include "../../Collider/ColliderBox.h"

#include "../../Object/Character/CharacterBase.h"
#include "../../Object/Character/Player.h"
#include "../../Object/ActorBase.h"

#include "ComponentAvilityShot.h"

ComponentAvilityShot::ComponentAvilityShot(Player& owner)
	: ComponentAvilityBase(owner),
	collisionManager_(CollisionManager::GetInstance()),
	inputManager_(InputManager::GetInstance()),
	moveAmount_({}),
	chageTime_(0.0f),
	coolTimer_(0.0f),
	shotVec_({}),
	shotAngle_(0.0f),
	effectId_(-1),
	isReflected_(false),
	gravityDir_(ParameterActor::DIR::MAX)
{
	type_ = AvilityTypes::TYPE::SHOT;
	stateFunctionMap_ =
	{
		{"input", [this]() { return ProcessInputShot(); }},		// 入力待ち状態
		{"charge", [this]() { return ProcessInputCharge(); }},	// チャージ状態
		{"shot", [this]() { return ProcessMoveShot(); }}		// ショット移動状態
	};
	currentState_ = "input";
	currentStateFunction_ = stateFunctionMap_[currentState_];
}

ComponentAvilityShot::~ComponentAvilityShot()
{
	if (attackCollider_)
	{
		attackCollider_->Delete();
		attackCollider_ = nullptr;
	}
}

void ComponentAvilityShot::Create()
{
	ComponentAvilityBase::Create();
	Init();
}

void ComponentAvilityShot::Init()
{
	// コライダーの登録
	attackCollider_ = owner_.CreateColliderClone();
	attackCollider_->ChangeTag(CollisionTags::TAG::PLAYER_AVILITY_SHOT);
	attackCollider_->SetIsActive(false);
	CollisionManager::GetInstance().Add(attackCollider_);

	// 状態の初期化
	currentState_ = "input";
	currentStateFunction_ = stateFunctionMap_[currentState_];

	if (gravityDir_ == ParameterActor::DIR::RIGHT)
	{
		parameter_.angle_ = UtilityCommon::Deg2RadF(0.0f);
	}
	else if (gravityDir_ == ParameterActor::DIR::LEFT)
	{
		parameter_.angle_ = UtilityCommon::Deg2RadF(90.0f);
	}
	else if (gravityDir_ == ParameterActor::DIR::UP)
	{
		parameter_.angle_ = UtilityCommon::Deg2RadF(180.0f);
	}
	else if (gravityDir_ == ParameterActor::DIR::DOWN)
	{
		parameter_.angle_ = UtilityCommon::Deg2RadF(0.0f);
	}

	// 自身のコライダーの判定を有効にする
	owner_.SetColliderActive(true);

	// コンポーネントの活動状態を戻す
	owner_.SetComponentActive("gravity", true);
	owner_.SetStateComponentActive(Player::STATE::ALIVE, true);

	// 攻撃判定用コライダーを無効にする
	attackCollider_->SetIsActive(false);

	shotVec_ = {};
	shotAngle_ = 0.0f;

	parameter_.shotVec_ = {};

	// エフェクトを止める
	if (effectId_ > -1)
	{
		effectManager_.Delete(effectId_);
	}
}

void ComponentAvilityShot::Update()
{
	// バウンドで停止したよう
	if (!isActive_) {

		return;
	}

	// 移動量の初期化
	moveAmount_ = {};
	moveAmount_ = parameter_.moveAmount_;

	// パラメータの取得
	pos_ = parameter_.pos_;
	defaultSize_ = parameter_.hitSize_;
	gravityDir_ = parameter_.gravityDir_;

	// 重力方向に合わせたサイズ調整
	bool isVerticalGravity = (gravityDir_ == ParameterActor::DIR::UP || gravityDir_ == ParameterActor::DIR::DOWN);
	nowSize_.x = isVerticalGravity ? defaultSize_.x : defaultSize_.y;
	nowSize_.y = isVerticalGravity ? defaultSize_.y : defaultSize_.x;

	// 状態関数の呼び出し
	currentStateFunction_();

}

void ComponentAvilityShot::Remove()
{
	if (attackCollider_)
	{
		attackCollider_->Delete();
		attackCollider_ = nullptr;
	}

	// 攻撃力を戻す
	//owner_.AddAttackPower(-ADD_ATTACK_POWER);
}

void ComponentAvilityShot::ProcessInputShot()
{
	// 横向きにしか撃てないようにするため、縦の入力は無視する
	const float moveSpeed = parameter_.moveSpeed_;

	// クールタイム減算
	coolTimer_ -= sceneManager_.GetDeltaTime();

	//　ショット入力があったらCharge開始(現在Qキー)
	if (coolTimer_ <= 0.0f && inputManager_.IsTrgDown(InputManager::TYPE::AVILITY_SHOT, parameter_.padNo_) && !parameter_.isAction_)
	{
		// 影響を与えるコンポーネントを無効にする
		owner_.SetStateComponentActive(Player::STATE::ALIVE, false);
		owner_.SetComponentActive("gravity", false);	
		owner_.SetAllAvilityComponentActive(false);
		isActive_ = true;

		// ジャンプ力をなくす
		parameter_.jumpPow_ = 0.0f;

		//!parameter_.direction_ ? shotAngle_ = UtilityCommon::Deg2RadF(0.0f) : shotAngle_ = UtilityCommon::Deg2RadF(180.0f);

		parameter_.shotTime_ = 0.0f;
		currentState_ = "charge";
		currentStateFunction_ = stateFunctionMap_[currentState_];

		// 初期化
		shotVec_ = {};
		shotAngle_ = 0.0f;

		// 攻撃判定有効
		parameter_.isAction_ = true;

		// 効果音再生
		soundManager_.PlaySe(SoundType::SE::ABILITY_SHOT_CHARGE);

		// エフェクト再生
		SpriteEffectManager::CreateParameter parameter;
		parameter.pos = parameter_.pos_;
		parameter.angle = parameter_.angle_;
		parameter.resourceKey = "shotCharge";
		parameter.animationSpeed = 0.3f;
		parameter.isLoop = true;
		parameter.target = &owner_;
		effectId_ = effectManager_.Create(parameter);
	}
}

void ComponentAvilityShot::ProcessInputCharge()
{
	// 現在の向きを入れる
	shotVec_.x = parameter_.direction_ ? -1 : 1;

	// =========================
	// ここで角度を決定
	// 方向判定
	bool isInput = false;
	if (inputManager_.IsNew(InputManager::TYPE::AVILITY_GRAVITY_RIGHT, parameter_.padNo_))
	{
		shotAngle_ += 0.1f;
		isInput = true;
	}
	if (inputManager_.IsNew(InputManager::TYPE::AVILITY_GRAVITY_LEFT, parameter_.padNo_))
	{
		shotAngle_ -= 0.1f;
		isInput = true;
	}
	//if (shotAngle_ > UtilityCommon::Deg2RadF(360.0f))
	//{
	//	shotAngle_ = 0.0f;
	//}

	// 入力されていない場合
	if (!isInput)
	{
		// パッドの確認
		Vector2 overSize = inputManager_.GetKnockLStickSize(parameter_.padNo_);

		// 正規化
		overSize.Normalize();
		
		// スティックを傾けている場合
		if (overSize.Length() != 0.0f)
		{
			// 角度決定
			shotAngle_ = std::atan2f(overSize.x, -overSize.y);
		}
	}

	// =========================
	// 角度 → ベクトル
	// =========================

	shotVec_.x = std::cos(shotAngle_);
	shotVec_.y = std::sin(shotAngle_);
	parameter_.shotVec_ = shotVec_;

	// 値の入れ替え
	float tempX = shotVec_.x;
	shotVec_.x = shotVec_.y;
	shotVec_.y = -tempX;
	parameter_.shotVec_ = shotVec_;


	// =========================
	 //モデル角度
	// =========================

	parameter_.angle_ = shotAngle_;

	// =========================
	// チャージ
	// =========================

	if (inputManager_.IsNew(InputManager::TYPE::AVILITY_SHOT_CHARGE, parameter_.padNo_))
	{
		chageTime_ += 0.5f;
		parameter_.shotTime_ += 0.1f;

		moveAmount_.x = std::sin(chageTime_);
		moveAmount_.y = 0.0f;

		parameter_.moveAmount_ = moveAmount_;
	}
	else
	{

		// 時間の割り当て
		if (parameter_.shotTime_ > SHOT_TIME)
		{
			parameter_.shotTime_ = SHOT_TIME;
		}

		// チャージ時間初期化
		chageTime_ = 0.0f;

		// 自身のコライダーの判定を無効にする
		owner_.SetColliderActive(false);

		// 攻撃判定用コライダーを有効にする
		attackCollider_->SetIsActive(true);
		
		// 影響を与えそうなパラメータを初期化
		parameter_.jumpPow_ = 0.0f;
		parameter_.knockBackPower_ = Vector2F();
		parameter_.isGround_ = false;
		
		// 反射処理の初期化
		isReflected_ = false;

		// インターバル初期化
		parameter_.shotDamageInterval_ = -1.0f;

		// 効果音停止
		soundManager_.StopSe(SoundType::SE::ABILITY_SHOT_CHARGE);

		// 効果音再生
		soundManager_.PlaySe(SoundType::SE::ABILITY_SHOT_START);

		//カメラシェイク
		SceneManager::GetInstance().GetCamera().SetCameraShake(CAMERA_SHAKE_TIME, CAMERA_SHAKE_POWER);

		// 状態遷移
		currentState_ = "shot";
		currentStateFunction_ = stateFunctionMap_[currentState_];

		// チャージエフェクトを削除
		effectManager_.Delete(effectId_);
		effectId_ = -1;
	}
}

void ComponentAvilityShot::ProcessMoveShot()
{
	// 時間を減らす
	float deltaTime = sceneManager_.GetDeltaTime();
	parameter_.shotTime_ -= deltaTime;				// ショット時間
	parameter_.shotDamageInterval_ -= deltaTime;	// ショットダメージインターバル

	// 終了条件に当てはまる場合
	if (parameter_.shotTime_ <= 0.0f || (parameter_.shotVec_.x == 0.0f && parameter_.shotVec_.y == 0.0f))
	{ 		
		// 重力別角度初期化
		parameter_.angle_ = UtilityCommon::GetGravityDirRadAngle(parameter_.gravityDir_);

		// 自身のコライダーの判定を有効にする
		owner_.SetColliderActive(true);

		// コンポーネントの活動状態を戻す
		owner_.SetComponentActive("gravity", true);
		owner_.SetStateComponentActive(Player::STATE::ALIVE, true);

		// 攻撃判定用コライダーを無効にする
		attackCollider_->SetIsActive(false);

		// 全てのアビリティコンポーネントを有効にする
		owner_.SetAllAvilityComponentActive(true);

		// 攻撃判定無効
		parameter_.isAction_ = false;

		currentState_ = "input";
		currentStateFunction_ = stateFunctionMap_[currentState_];
		return;
	}
	else
	{
		Vector2F dir = parameter_.shotVec_;

		moveAmount_.y = dir.y * parameter_.shotTime_ * SHOT_SPEED;
		moveAmount_.x = dir.x * parameter_.shotTime_ * SHOT_SPEED;

		float currentAngle = std::atan2(dir.y, dir.x) - UtilityCommon::Deg2RadF(-90.0f);

		parameter_.angle_ = currentAngle;
	}

	// 各軸の衝突判定
	ProcessCollision(true);  // X軸
	ProcessCollision(false); // Y軸

	// 座標と移動量の更新
	parameter_.moveAmount_ = moveAmount_;
}

void ComponentAvilityShot::ProcessCollision(bool isXAxis)
{
	float& moveVal = isXAxis ? moveAmount_.x : moveAmount_.y;
	if (moveVal == 0.0f)
	{
		return;
	}

	float& currentPos = isXAxis ? pos_.x : pos_.y;

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
		checkParameter.pos = pos_.ToVector2();
		checkParameter.size = nowSize_;
		checkParameter.isXAxis = isXAxis;
		checkParameter.stepMove = stepMove;

		CollisionManager::CollisionResult result = collisionManager_.CheckStageCollision(checkParameter);

		if (result.isHit)
		{
			// 1個戻す
			currentPos -= stepMove;

			CheckGroundStatus(stepMove, isXAxis);

			// 反射ベクトル計算（共通化した法線を使用）
			Vector2F reflectDir = UtilityCommon::Reflect(parameter_.shotVec_, result.normal);
			parameter_.shotVec_ = reflectDir;

			// 反射回数・時間の調整
			if (!isReflected_)
			{
				isReflected_ = true;
				if (parameter_.shotTime_ > 0.5f)
				{
					parameter_.shotTime_ -= 0.35f;
				}
			}

			moveVal = 0.0f;
			break;
		}
		else
		{
			isReflected_ = false;
		}
	}
}
void ComponentAvilityShot::CheckGroundStatus(float moveVal, bool isXAxis)
{
	bool isGround = false;
	if (isXAxis)
	{
		if ((moveVal > 0.0f && gravityDir_ == ParameterActor::DIR::RIGHT) ||
			(moveVal < 0.0f && gravityDir_ == ParameterActor::DIR::LEFT)) isGround = true;
	}
	else
	{
		if ((moveVal > 0.0f && gravityDir_ == ParameterActor::DIR::DOWN) ||
			(moveVal < 0.0f && gravityDir_ == ParameterActor::DIR::UP)) isGround = true;
	}

	if (isGround) parameter_.isGround_ = true;
}
