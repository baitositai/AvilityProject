#include "../../Manager/Game/CollisionManager.h"
#include "../../Manager/Common/SceneManager.h"
#include "../../Object/Character/Enemy/EnemyBase.h"
#include "../../Object/Common/Animation.h"
#include "../../Collider/ColliderFan.h"
#include "../../Utility/UtilityCommon.h"
#include "ComponentLogicPatrol.h"

ComponentLogicPatrol::ComponentLogicPatrol(EnemyBase& owner) :
	ComponentLogicBase(owner),
	owner_(owner),
	parameter_(owner.GetParameter())
{
	moveDirection_ = 0.0f;
	eyeBaseAngle_ = 0.0f;
	stopTimer_ = 0.0f;
	moveDistance_ = {};
	isMove_ = false;
	state_ = STATE::PATROL;

	// 状態遷移処理のマップを初期化
	stateChangeMap_.emplace(STATE::PATROL, std::bind(&ComponentLogicPatrol::ChangeStatePatrol, this));
	stateChangeMap_.emplace(STATE::CHASE, std::bind(&ComponentLogicPatrol::ChangeStateChase, this));

	// 視野角用のコライダーを生成
	colliderFan_ = std::make_shared<ColliderFan>(owner_, CollisionTags::TAG::ENEMY_VIEW, owner_.GetParameter().pos_, parameter_.eyeDistance_, eyeBaseAngle_, parameter_.eyeAngleRad_);

	// コライダーの登録
	collisionManager_.Add(colliderFan_);
}

void ComponentLogicPatrol::Init()
{
	// 基底クラスの初期化
	ComponentLogicBase::Init();

	// 視野角の初期化
	UpdateEyeAngle();

	// 初期状態
	ChangeState(STATE::PATROL);
}

void ComponentLogicPatrol::Update()
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
}

void ComponentLogicPatrol::Remove()
{
	// コライダーの削除
	if (colliderFan_)
	{
		colliderFan_->Delete();
		colliderFan_ = nullptr;
	}
}

void ComponentLogicPatrol::UpdatePatrolLand()
{
	// ターゲットを発見した場合
	if (parameter_.isDiscover_)
	{
		// 状態遷移
		ChangeState(STATE::CHASE);
		return;
	}

	if (isMove_)
	{
		// 移動処理
		float moveStep = parameter_.moveSpeed_ * moveDirection_;
		parameter_.moveAmount_.x += moveStep;

		// 移動した絶対値分だけ残り移動距離を減算
		moveDistance_.x -= fabsf(moveStep);

		// 移動距離が0以下になったら停止
		if (moveDistance_.x <= 0.0f)
		{
			moveDistance_.x = 0.0f;
			isMove_ = false;

			// 待機時間をランダム決定
			stopTimer_ = static_cast<float>(GetRand(150)) / 100.0f + 0.5f;
		}
	}
	else
	{
		// タイマーをデルタタイムで減算
		stopTimer_ -= sceneManager_.GetDeltaTime();

		// 時間が終了した場合
		if (stopTimer_ <= 0.0f)
		{
			isMove_ = true;

			// 移動距離をランダム決定
			moveDistance_.x = static_cast<float>(GetRand(200)) + 1.0f;

			// 移動方向を決定
			moveDirection_ = (GetRand(2) == 0) ? -1.0f : 1.0f;
		}
	}
}

void ComponentLogicPatrol::UpdatePatrolAir()
{
	// ターゲットを発見した場合
	if (parameter_.isDiscover_)
	{
		// 状態遷移
		ChangeState(STATE::CHASE);
		return;
	}

	if (isMove_)
	{
		// 移動処理
		float moveStep = parameter_.moveSpeed_ * moveDirection_;
		parameter_.moveAmount_.x += moveStep;
		parameter_.moveAmount_.y += moveStep;

		// 移動した絶対値分だけ残り移動距離を減算
		moveDistance_.x -= fabsf(moveStep);
		moveDistance_.y -= fabsf(moveStep);

		// XとYの両方の移動距離が0以下になったら停止
		if (moveDistance_.x <= 0.0f && moveDistance_.y <= 0.0f)
		{
			moveDistance_.x = 0.0f;
			moveDistance_.y = 0.0f;
			isMove_ = false;

			// 待機時間をランダム決定
			stopTimer_ = static_cast<float>(GetRand(150)) / 100.0f + 0.5f;
		}
	}
	else
	{
		// タイマーをデルタタイムで減算
		stopTimer_ -= sceneManager_.GetDeltaTime();

		// 時間が終了した場合
		if (stopTimer_ <= 0.0f)
		{
			isMove_ = true;

			// 移動距離をランダム決定
			float randomDistance = static_cast<float>(GetRand(200)) + 1.0f;
			moveDistance_.x = randomDistance;
			moveDistance_.y = randomDistance;

			// 移動方向を決定
			moveDirection_ = (GetRand(2) == 0) ? -1.0f : 1.0f;
		}
	}
}

void ComponentLogicPatrol::UpdateChase()
{
	// ターゲットの座標が存在しない場合
	if (parameter_.targetPos_ == nullptr)
	{
		// 終了判定
		isEnd_ = true;

		// パトロールへ
		//ChangeState(STATE::PATROL);
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
	}

	// ターゲットから離れた場合 見失う距離まで離れたか
	else if (distance >= parameter_.eyeDistance_)
	{
		// パトロールに変更
		ChangeState(STATE::PATROL);

		// ターゲット座標を空にする
		parameter_.targetPos_ = nullptr;
	}
}

void ComponentLogicPatrol::ChangeState(const STATE state)
{
	// 状態
	state_ = state;

	// 状態遷移処理
	stateChangeMap_[state_]();
}

void ComponentLogicPatrol::ChangeStatePatrol()
{
	// 移動種類別に更新処理を設定
	if (parameter_.habitatType_ == ParameterEnemy::HABITAT_TYPE::LAND)
	{
		update_ = std::bind(&ComponentLogicPatrol::UpdatePatrolLand, this);
	}
	else if (parameter_.habitatType_ == ParameterEnemy::HABITAT_TYPE::AIR)
	{
		update_ = std::bind(&ComponentLogicPatrol::UpdatePatrolAir, this);
	}

	// 初期化処理
	stopTimer_ = 0.0f;
	moveDistance_ = {};
	isMove_ = true;
	parameter_.isDiscover_ = false;
}

void ComponentLogicPatrol::ChangeStateChase()
{
	update_ = std::bind(&ComponentLogicPatrol::UpdateChase, this);
}

void ComponentLogicPatrol::UpdateEyeAngle()
{
	// キャラクターの向きに応じてコライダーの角度を更新
	eyeBaseAngle_ = parameter_.angle_;
	eyeBaseAngle_ = parameter_.direction_ ? DX_PI_F : 0.0f;
}

void ComponentLogicPatrol::UpdateAnimation()
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
