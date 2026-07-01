#include <DxLib.h>
#include "../../Application.h"
#include "../../Manager/Game/CollisionManager.h"
#include "../../Object/Character/Enemy/EnemyMaid.h"
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
	isMove_ = false;
	state_ = STATE::COLLECT;

	// 状態遷移処理のマップを初期化
	changeStateMap_.emplace(STATE::COLLECT, std::bind(&ComponentLogicMaid::ChangeStateCollect, this));
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
	parameter.interval_ = 5.0f;
	parameter.fallDirList_ = { ParameterActor::DIR::DOWN,ParameterActor::DIR::RIGHT,ParameterActor::DIR::LEFT,ParameterActor::DIR::UP };
	parameter.limitCount_ = 5;
	constexpr int OFFSET = 150;
	parameter.createRangeTopLeft_ = { OFFSET,OFFSET };
	parameter.createRangeBottomRight_ = { Application::SCREEN_SIZE_X - OFFSET, Application::SCREEN_SIZE_Y - OFFSET };
	foodShawer_ = std::make_unique<FoodShawer>(parameter);

	// 初期化処理
	Init();
}

void ComponentLogicMaid::Init()
{
	// フードシャワー
	foodShawer_->Init();

	// 状態遷移
	ChangeState(STATE::COLLECT);
}

void ComponentLogicMaid::Update()
{
	update_();
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
	foodShawer_->Update();

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

	// 視野コライダー判定を無効
	colliderFan_->SetIsActive(true);
}

void ComponentLogicMaid::UpdateEyeAngle()
{
	// キャラクターの向きに応じてコライダーの角度を更新
	eyeBaseAngle_ = parameter_.angle_;
	eyeBaseAngle_ = parameter_.direction_ ? DX_PI_F : 0.0f;
}