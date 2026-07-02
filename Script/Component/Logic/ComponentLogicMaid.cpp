#include <DxLib.h>
#include "../../Application.h"
#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Game/CollisionManager.h"
#include "../../Manager/Game/ItemManager.h"
#include "../../Manager/Game/PlayerManager.h"
#include "../../Object/Character/Player.h"
#include "../../Object/Character/Enemy/EnemyMaid.h"
#include "../../Object/Item/ItemBase.h"
#include "../../Utility/UtilityCommon.h"
#include "../../Collider/ColliderFan.h"
#include "../../System/FoodShawer.h"
#include "ComponentLogicMaid.h"

ComponentLogicMaid::ComponentLogicMaid(EnemyMaid& owner):
	ComponentLogicBase(owner),
	owner_(owner),
	parameter_(owner.GetParameter())
{
	moveDirection_ = 0.0f;
	eyeBaseAngle_ = 0.0f;
	stopTimer_ = 0.0f;
	moveDistance_ = {};
	timer_ = 0.0f;
	isMove_ = false;
	timer_ = 0.0f;
	state_ = STATE::COLLECT;
	nextGravityDir_ = ParameterActor::DIR::MAX;

	// 状態遷移処理のマップを初期化
	changeStateMap_.emplace(STATE::COLLECT, std::bind(&ComponentLogicMaid::ChangeStateCollect, this));
	changeStateMap_.emplace(STATE::JUMP, std::bind(&ComponentLogicMaid::ChangeStateJump, this));
	changeStateMap_.emplace(STATE::STAMP_READY, std::bind(&ComponentLogicMaid::ChangeStateStampReady, this));
	changeStateMap_.emplace(STATE::STAMP, std::bind(&ComponentLogicMaid::ChangeStateStamp, this));
}

ComponentLogicMaid::~ComponentLogicMaid()
{
}

void ComponentLogicMaid::Create()
{
	// 視野角用のコライダーを生成
	colliderFan_ = std::make_shared<ColliderFan>(owner_, CollisionTags::TAG::ENEMY_VIEW, owner_.GetParameter().pos_, parameter_.eyeDistance_, eyeBaseAngle_, parameter_.eyeAngleRad_);

	// コライダーの登録
	collisionManager_.Add(colliderFan_);

	// フードシャワー
	FoodShawer::Parameter parameter;
	parameter.interval_ = 3.0f;
	parameter.fallDirList_ = { ParameterActor::DIR::DOWN,ParameterActor::DIR::RIGHT,ParameterActor::DIR::LEFT,ParameterActor::DIR::UP };
	parameter.limitCount_ = 10;
	constexpr int OFFSET = 150;
	parameter.createRangeTopLeft_ = { OFFSET,OFFSET };
	parameter.createRangeBottomRight_ = { Application::SCREEN_SIZE_X - OFFSET, Application::SCREEN_SIZE_Y - OFFSET };
	foodShawer_ = std::make_unique<FoodShawer>(parameter);

	// 初期化処理
	Init();
}

void ComponentLogicMaid::Init()
{
	// 基底クラスの初期化
	ComponentLogicBase::Init();

	// フードシャワー
	foodShawer_->Init();

	// 状態遷移
	ChangeState(STATE::COLLECT);

	// 視野角の初期化
	UpdateEyeAngle();
}

void ComponentLogicMaid::Update()
{
	// 状態別更新
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

void ComponentLogicMaid::Remove()
{
	if (colliderFan_)
	{
		colliderFan_->Delete();
	}
}

void ComponentLogicMaid::AttackReset()
{

}

void ComponentLogicMaid::UpdateCollect()
{	
	// 発見判定
	if(parameter_.isDiscover_)
	{
		// 状態遷移
		owner_.ChangeState(EnemyMaid::STATE::ATTACK);

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
		
		// ターゲットの発見判定をリセット
		parameter_.isDiscover_ = false;
		return;
	}

	Vector2F moveDir = {};
	float distance = 0.0f;
	ParameterEnemyMaid::DIR gravityDir = parameter_.gravityDir_;

	// フードシャワーの更新
	foodShawer_->Update();

	// 一番近い食べ物を取得
	const ItemBase* targetFood = itemManager_.GetNearestFood(parameter_.pos_);

	// 存在する場合
	if (targetFood)
	{	
		// ターゲットへの方向を取得
		moveDir = Vector2F::SubVector2F(targetFood->GetParameter().pos_, parameter_.pos_);

		// ターゲットの重力方向を取得
		gravityDir = targetFood->GetParameter().gravityDir_;
	}
	else
	{
		// 最も現在地から近いプレイヤーを取得
		const Player* nearestPlayer = playerManager_.GetNearestPlayer(parameter_.pos_);

		// 存在する場合
		if (nearestPlayer)
		{
			// プレイヤーのパラメータを取得
			auto& playerParameter = nearestPlayer->GetParameter();

			// プレイヤーを追いかけるための方向を取得
			moveDir = Vector2F::SubVector2F(playerParameter.pos_, parameter_.pos_);

			// ターゲットの重力方向を取得
			gravityDir = playerParameter.gravityDir_;
		}
		else
		{
			// プレイヤーが存在しない場合は移動しない
			moveDir = Vector2F(0.0f, 0.0f);
		}
	}	

	// ベクトルの長さを計算して距離を求める
	distance = moveDir.Length();
	
	// ターゲットに向かって移動
	if (distance > 0.01f)
	{
		moveDir = Vector2F(moveDir.x / distance, moveDir.y / distance);
		Vector2F velocity = Vector2F::MulVector2FFloat(moveDir.Normalize(), parameter_.moveSpeed_);
		parameter_.moveAmount_ = velocity;
	}

	// タイマーが0未満で、重力方向が変化している場合
	if(timer_ < 0.0f && parameter_.gravityDir_ != gravityDir)
	{
		// スタンプへ切り替えるタイマーをリセット
		timer_ = CHANGE_GRAVITY_TIME;
		
		// 状態遷移
		ChangeState(STATE::JUMP);	
		
		// 重力方向の更新
		nextGravityDir_ = gravityDir;
	}
	else
	{
		// タイマーを減算
		timer_ -= sceneManager_.GetDeltaTime();
	}
}

void ComponentLogicMaid::UpdateJump()
{
	// ジャンプ力が一定値以上の場合
	const float HIGHEST = -parameter_.jumpPowMax_ / 2.0f + 2.0f;
	if (parameter_.jumpPow_ >= HIGHEST)
	{
		// 状態遷移
		ChangeState(STATE::STAMP_READY);
	}	
}

void ComponentLogicMaid::UpdateStampReady()
{
	timer_ -= sceneManager_.GetDeltaTime();
	if (timer_ < 0.0f)
	{
		ChangeState(STATE::STAMP);
	}
}

void ComponentLogicMaid::UpdateStamp()
{
	if (parameter_.isGround_)
	{
		// 状態遷移
		ChangeState(STATE::COLLECT);
	
		// 重力をもとに戻す
		parameter_.gravityPower_ -= ADD_GRAVITY;
	}
}

void ComponentLogicMaid::ChangeState(const STATE state)
{
	state_ = state;
	changeStateMap_[state_]();
}

void ComponentLogicMaid::ChangeStateCollect()
{
	update_ = std::bind(&ComponentLogicMaid::UpdateCollect, this);

	// 初期アニメーションの再生
	owner_.GetAnimation().Play(Animation::TYPE::IDLE, true);

	// 視野コライダー判定を有効
	colliderFan_->SetIsActive(true);

	// タイマー初期化
	timer_ = CHANGE_GRAVITY_TIME;
}

void ComponentLogicMaid::ChangeStateJump()
{
	update_ = std::bind(&ComponentLogicMaid::UpdateJump, this);
	
	// 視野コライダー判定を無効
	colliderFan_->SetIsActive(false);

	// 地面判定を無効
	parameter_.isGround_ = false;

	// ジャンプ力設定
	owner_.SetJumpPow(-parameter_.jumpPowMax_);

	// 待機アニメーションを再生
	owner_.GetAnimation().Play(Animation::TYPE::JUMP, false);

	// タイマー初期化
	timer_ = STOP_TIME;
}

void ComponentLogicMaid::ChangeStateStampReady()
{
	update_ = std::bind(&ComponentLogicMaid::UpdateStampReady, this);

	// 次の重力を設定
	parameter_.gravityDir_ = nextGravityDir_;

	// 角度の更新
	parameter_.angle_ = UtilityCommon::GetGravityDirRadAngle(nextGravityDir_);

	// ジャンプ力を0にする
	owner_.SetJumpPow(0.0f);

	// ジャンプアニメーション
	owner_.GetAnimation().Play(Animation::TYPE::IDLE);

	// 重力を無効化
	owner_.SetComponentActive("gravity", false);

	// 衝突判定を行うために無理やり移動量を追加
	parameter_.moveAmount_.x += 0.1f;
}

void ComponentLogicMaid::ChangeStateStamp()
{
	update_ = std::bind(&ComponentLogicMaid::UpdateStamp, this);

	// 重力を加速
	parameter_.gravityPower_ += ADD_GRAVITY;

	// 重力を有効化
	owner_.SetComponentActive("gravity", true);
}

void ComponentLogicMaid::UpdateEyeAngle()
{
	// キャラクターの向きに応じてコライダーの角度を更新
	eyeBaseAngle_ = parameter_.angle_;
	eyeBaseAngle_ += parameter_.direction_ ? DX_PI_F : 0.0f;
}

void ComponentLogicMaid::UpdateAnimation()
{
	Animation& animation = owner_.GetAnimation();
	Animation::TYPE type = Animation::TYPE::MAX;

	// 移動しているかどうかの判定
	if (parameter_.moveAmount_.x != 0.0f || parameter_.moveAmount_.y != 0.0f)
	{
		type = Animation::TYPE::WALK;

		// 重力方向に応じて、チェックする移動量の軸を切り替える
		if (parameter_.gravityDir_ == ParameterActor::DIR::DOWN)
		{
			// 通常（地面）：右移動で通常、左移動で反転
			parameter_.direction_ = (parameter_.moveAmount_.x < 0.0f);
		}
		else if (parameter_.gravityDir_ == ParameterActor::DIR::UP)
		{
			// 天井：通常とは上下反転しているため、左移動で通常、右移動で反転
			parameter_.direction_ = (parameter_.moveAmount_.x > 0.0f);
		}
		else if (parameter_.gravityDir_ == ParameterActor::DIR::LEFT)
		{
			// 左の壁：上に向かって進むときが通常、下に向かって進むときが反転
			parameter_.direction_ = (parameter_.moveAmount_.y < 0.0f);
		}
		else if (parameter_.gravityDir_ == ParameterActor::DIR::RIGHT)
		{
			// 右の壁：下に向かって進むときが通常、上に向かって進むときが反転
			parameter_.direction_ = (parameter_.moveAmount_.y > 0.0f);
		}
	}
	else
	{
		type = Animation::TYPE::IDLE;
	}

	if (animation.GetType() == type)
	{
		return;
	}

	animation.Play(type);
}