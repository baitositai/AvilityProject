#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Game/CollisionManager.h"
#include "../../Manager/Game/GimmickManager.h"
#include "../../Collider/ColliderCircle.h"
#include "../../Object/Common/Animation.h"
#include "../../Object/Character/Enemy/EnemyPanda.h"
#include "../../Utility/UtilityCommon.h"
#include "ComponentLogicBambooGrowing.h"

ComponentLogicBambooGrowing::ComponentLogicBambooGrowing(EnemyPanda& owner) :
	ComponentLogicBase(owner),
	owner_(owner),
	parameter_(owner.GetParameter())
{
	// 変数の初期化
	createBambooCount_ = -1;
	attackPos_ = {};
	createBambooPos_ = {};
	attackCollider_ = nullptr;
	state_ = STATE::ANIMATION;

	// 状態遷移処理のマップを初期化
	changeStateMap_.emplace(STATE::ANIMATION, std::bind(&ComponentLogicBambooGrowing::ChangeStateAnimation, this));
	changeStateMap_.emplace(STATE::GROWING, std::bind(&ComponentLogicBambooGrowing::ChangeStateGrowing, this));
}

ComponentLogicBambooGrowing::~ComponentLogicBambooGrowing()
{
}

void ComponentLogicBambooGrowing::Create()
{
	// 攻撃用コライダーの登録
	attackCollider_ = std::make_shared<ColliderCircle>(owner_, parameter_.attackCollisionTag_, attackPos_, parameter_.defaultAttackRadius_);
	attackCollider_->SetIsActive(false);
	collisionManager_.Add(attackCollider_);
}

void ComponentLogicBambooGrowing::Init()
{
	ComponentLogicBase::Init();
	ChangeState(STATE::ANIMATION);
	createBambooCount_ = UtilityCommon::GetRandomCount(4, 6);
}

void ComponentLogicBambooGrowing::Update()
{
	update_();
}

void ComponentLogicBambooGrowing::Remove()
{
	if (attackCollider_)
	{
		attackCollider_->Delete();
		attackCollider_ = nullptr;
	}
}

void ComponentLogicBambooGrowing::UpdateAnimation()
{
	Animation& animation = owner_.GetAnimation();
	if (animation.GetAnimationIndex() >= owner_.GetParameter().defaultAttackStartFrame_)
	{
		// 攻撃のコライダー設定
		attackCollider_->SetIsActive(true);

		// 状態遷移
		ChangeState(STATE::GROWING);
	}
}

void ComponentLogicBambooGrowing::UpdateGrowing()
{
	Animation& animation = owner_.GetAnimation();

	createIntervalTime_ -= sceneManager_.GetDeltaTime();
	if (createIntervalTime_ < 0.0f)
	{
		// インターバル設定
		createIntervalTime_ = INTERVAL_TIME;

		// 伸びる竹を生成
		CreateBamboo();

		// 生成回数減少
		createBambooCount_--;
		if (createBambooCount_ < 1)
		{
			isEnd_ = true;
			return;
		}
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

		// 待機姿勢
		animation.Play(Animation::TYPE::IDLE);
	}
}

void ComponentLogicBambooGrowing::ChangeState(const STATE state)
{
	state_ = state;
	changeStateMap_[state_]();
}

void ComponentLogicBambooGrowing::ChangeStateAnimation()
{
	update_ = std::bind(&ComponentLogicBambooGrowing::UpdateAnimation, this);
}

void ComponentLogicBambooGrowing::ChangeStateGrowing()
{
	update_ = std::bind(&ComponentLogicBambooGrowing::UpdateGrowing, this);

	// 一つ目の竹の生成位置
	createBambooPos_ = parameter_.GetFootPos();
	Vector2F dir = Vector2F::MulVector2FFloat(parameter_.GetFront(), parameter_.scale_);
	createBambooPos_ = Vector2F::AddVector2F(parameter_.GetFootPos(), Vector2F::MulVector2FFloat(dir, parameter_.defaultAttackDistance_));
}

void ComponentLogicBambooGrowing::CreateBamboo()
{
	// 竹生成
	GimmickManager::CreateParameter createParameter = {};
	createParameter.type = GimmickTypes::TYPE::GROWING_BAMBOO;
	createParameter.pos = parameter_.GetFootPos();
	createParameter.attackPower = 40;
	gimmickManager_.Create(createParameter);

	// 竹の生成位置を調整
	createBambooPos_.x += CREATE_OFFSET_X;
}