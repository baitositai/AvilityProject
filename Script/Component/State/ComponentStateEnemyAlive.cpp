#include "../../Manager/Game/CollisionManager.h"
#include "../../Manager/Common/SceneManager.h"
#include "../../Object/Character/Enemy/EnemyBase.h"
#include "../../Object/Common/Animation.h"
#include "../../Collider/ColliderFan.h"
#include "../../Utility/UtilityCommon.h"
#include "ComponentStateEnemyAlive.h"

ComponentStateEnemyAlive::ComponentStateEnemyAlive(EnemyBase& owner) :
	ComponentCharacterStateBase(owner),
	owner_(owner),
	parameter_(owner.GetParameter()),
	sceneManager_(SceneManager::GetInstance())
{
	moveTimer_ = 0.0f;
	isMove_ = false;
	state_ = STATE::PATROL;

	// 状態遷移処理のマップを初期化
	stateChangeMap_.emplace(STATE::PATROL, std::bind(&ComponentStateEnemyAlive::ChangeStatePatrol, this));
	stateChangeMap_.emplace(STATE::CHASE, std::bind(&ComponentStateEnemyAlive::ChangeStateChase, this));
}

ComponentStateEnemyAlive::~ComponentStateEnemyAlive()
{
}

void ComponentStateEnemyAlive::Init()
{
	// 視野角用のコライダーを生成
	colliderFan_ = std::make_shared<ColliderFan>(owner_, CollisionTags::TAG::ENEMY_VIEW, owner_.GetParameter().pos_, parameter_.eyeDistance_, parameter_.eyeAngleRad_);

	// コライダーの登録
	CollisionManager::GetInstance().Add(colliderFan_);

	// 初期状態
	ChangeState(STATE::PATROL);
}

void ComponentStateEnemyAlive::Update()
{
	update_();
}

void ComponentStateEnemyAlive::UpdatePatrol()
{
	// ターゲットを発見した場合
	if (parameter_.isDiscover_)
	{
		// 状態遷移
		ChangeState(STATE::CHASE);
		return;
	}

	// タイマーをデルタタイムで減算
	moveTimer_ -= sceneManager_.GetDeltaTime();

	// 時間が終了した場合
	if (moveTimer_ <= 0.0f)
	{
		// 状態を反転
		isMove_ = !isMove_;

		if (isMove_)
		{
			// 移動時間の決定 1.0秒から3.0秒の間でランダム
			moveTimer_ = static_cast<float>(GetRand(200)) / 100.0f + 1.0f;
			
			// 移動アニメーションを開始
			owner_.GetAnimation().Play(Animation::TYPE::WALK);
		}
		else
		{
			// 待機時間の決定 0.5秒から2.0秒の間でランダム
			moveTimer_ = static_cast<float>(GetRand(150)) / 100.0f + 0.5f;

			// 待機アニメーションを開始
			owner_.GetAnimation().Play(Animation::TYPE::IDLE);
		}
	}

	// 現在の状態に応じた処理
	if (isMove_)
	{
		// 左に進む デルタタイムを掛けて移動距離を均一化
		parameter_.moveAmount_.x -= parameter_.moveSpeed_;
	}
}

void ComponentStateEnemyAlive::UpdateChase()
{
	// ターゲットの座標が存在しない場合
	if (parameter_.targetPos_ == nullptr)
	{
		// パトロールへ
		ChangeState(STATE::PATROL);
		return;
	}

	// ターゲットへの方向ベクトルを計算
	Vector2F direction = Vector2F::SubVector2F(*parameter_.targetPos_, parameter_.pos_);

	// ベクトルの長さを計算して距離を求める
	float distance = direction.Length();

	// ターゲットに向かって移動 向きを正規化して速度とデルタタイムを掛ける
	if (distance > 0.0f)
	{
		direction = Vector2F(direction.x / distance, direction.y / distance);
		Vector2F velocity = Vector2F::MulVector2FFloat(direction, parameter_.moveSpeed_);
		parameter_.moveAmount_ = Vector2F::AddVector2F(parameter_.pos_, velocity);
	}

	// ターゲットに近づいた場合 攻撃間合いに入ったか
	if (distance <= parameter_.attackStartDistance_)
	{
		owner_.ChangeState(EnemyBase::STATE::ATTACK);
	}
	// ターゲットから離れた場合 見失う距離まで離れたか
	else if (distance >= parameter_.loseSightDistance_)
	{
		ChangeState(STATE::PATROL);
	}
}

void ComponentStateEnemyAlive::ChangeState(const STATE state)
{
	// 状態
	state_ = state;

	// 状態遷移処理
	stateChangeMap_[state_]();
}

void ComponentStateEnemyAlive::ChangeStatePatrol()
{
	update_ = std::bind(&ComponentStateEnemyAlive::UpdatePatrol, this);

	// 初期化処理
	moveTimer_ = 0.0f;
	isMove_ = true;
}

void ComponentStateEnemyAlive::ChangeStateChase()
{
	update_ = std::bind(&ComponentStateEnemyAlive::UpdateChase, this);
}