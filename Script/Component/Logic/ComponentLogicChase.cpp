#include "../../Manager/Game/CollisionManager.h"
#include "../../Manager/Game/PlayerManager.h"
#include "../../Manager/Common/SceneManager.h"
#include "../../Object/Character/Enemy/EnemyBase.h"
#include "../../Object/Common/Animation.h"
#include "../../Collider/ColliderFan.h"
#include "../../Utility/UtilityCommon.h"
#include "ComponentLogicChase.h"

#include "../../Object/Character/Player.h"

ComponentLogicChase::ComponentLogicChase(EnemyBase& owner) :
	ComponentLogicBase(owner),
	owner_(owner),
	parameter_(owner.GetParameter())
{
	moveDirection_ = 0.0f;
	eyeBaseAngle_ = 0.0f;
	stopTimer_ = 0.0f;
	moveDistance_ = {};
	isMove_ = false;
	state_ = STATE::CHASE;

	// 状態遷移処理のマップを初期化
	changeStateMap_.emplace(STATE::NONE, std::bind(&ComponentLogicChase::ChangeStateChase, this));
	changeStateMap_.emplace(STATE::CHASE, std::bind(&ComponentLogicChase::ChangeStateChase, this));
}

ComponentLogicChase::~ComponentLogicChase()
{
}

void ComponentLogicChase::Create()
{
	// 視野角用のコライダーを生成
	colliderFan_ = std::make_shared<ColliderFan>(owner_, CollisionTags::TAG::ENEMY_VIEW, owner_.GetParameter().pos_, parameter_.eyeDistance_, eyeBaseAngle_, parameter_.eyeAngleRad_);

	// コライダーの登録
	collisionManager_.Add(colliderFan_);

	// 初期化処理
	Init();
}

void ComponentLogicChase::Init()
{
	// 基底クラスの初期化
	ComponentLogicBase::Init();

	// 視野角の初期化
	UpdateEyeAngle();

	// 初期状態
	ChangeState(STATE::CHASE);
}

void ComponentLogicChase::Update()
{
	update_();

	// 状態が生存の場合
	if (owner_.GetState() == CharacterBase::STATE::ALIVE)
	{
		// 視野角の更新
		UpdateEyeAngle();

		// アニメーションの更新
		UpdateAnimation();
	}

	// 一番近いプレイヤーをターゲットに
	const auto* nearestPlayer = playerManager_.GetNearestPlayer(parameter_.pos_);
	if (nearestPlayer != nullptr)
	{
		parameter_.targetPos_ = &nearestPlayer->GetParameter().pos_;
	}
	else
	{
		parameter_.targetPos_ = nullptr;
	}
}

void ComponentLogicChase::Remove()
{
	// コライダーの削除
	if (colliderFan_)
	{
		colliderFan_->Delete();
		colliderFan_ = nullptr;
	}
}

void ComponentLogicChase::AttackReset()
{
}

void ComponentLogicChase::UpdateChase()
{
	// ターゲットの座標が存在しない場合
	if (parameter_.targetPos_ == nullptr)
	{
		// 終了判定
		isEnd_ = true;

		// 視野コライダー判定を無効
		colliderFan_->SetIsActive(false);
		return;
	}

	// ターゲットへの方向ベクトルを計算
	Vector2F direction = Vector2F::SubVector2F(*parameter_.targetPos_, parameter_.pos_);

	// ベクトルの長さを計算して距離を求める
	float distance = direction.Length();

	// ターゲットに向かって移動
	if (distance > 0.0f)
	{
		direction = Vector2F(direction.x / distance, direction.y / distance);
		Vector2F velocity = Vector2F::MulVector2FFloat(direction, parameter_.moveSpeed_);
		parameter_.moveAmount_ = velocity;
	}

	// ターゲットに近づいた場合 攻撃間合いに入ったか
	if (distance <= parameter_.attackStartDistance_)
	{
		// 攻撃に変更
		owner_.ChangeState(EnemyBase::STATE::ATTACK);

		// 攻撃のアニメーションを開始（ループしない）
		owner_.GetAnimation().Play(Animation::TYPE::ATTACK, false);

		// 次回アニメーションを指定しない
		owner_.GetAnimation().SetNextAnimationType(Animation::TYPE::MAX);

		// 攻撃判定
		parameter_.isAction_ = true;

		// 終了判定
		isEnd_ = true;

		// 視野コライダー判定を無効
		colliderFan_->SetIsActive(false);
	}
	//// ターゲットから離れた場合 見失う距離まで離れたか
	//else if (distance >= parameter_.eyeDistance_)
	//{
	//	// パトロールに変更
	//	ChangeState(STATE::PATROL);

	//	// ターゲット座標を空にする
	//	parameter_.targetPos_ = nullptr;
	//}
}

void ComponentLogicChase::ChangeState(const STATE state)
{
	// 状態
	state_ = state;

	// 状態遷移処理
	changeStateMap_[state_]();
}

void ComponentLogicChase::ChangeStateChase()
{
	update_ = std::bind(&ComponentLogicChase::UpdateChase, this);
}

void ComponentLogicChase::UpdateEyeAngle()
{
	// キャラクターの向きに応じてコライダーの角度を更新
	eyeBaseAngle_ = parameter_.angle_;
	eyeBaseAngle_ = parameter_.direction_ ? DX_PI_F : 0.0f;
}

void ComponentLogicChase::UpdateAnimation()
{
	Animation& animation = owner_.GetAnimation();
	Animation::TYPE type = Animation::TYPE::MAX;

	// 移動量がある場合
	if (parameter_.moveAmount_.x > 0.0f)
	{
		type = Animation::TYPE::WALK;
		parameter_.direction_ = false;
	}
	else if (parameter_.moveAmount_.x < 0.0f)
	{
		type = Animation::TYPE::WALK;
		parameter_.direction_ = true;
	}
	// ない場合
	else
	{
		type = Animation::TYPE::IDLE;
	}

	// 既にアニメーションが再生されてる場合
	if (owner_.GetAnimation().GetType() == type)
	{
		return;
	}

	// 待機のアニメーションに変更
	owner_.GetAnimation().Play(type);
}
