#include <tgmath.h>
#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Common/InputManager.h"
#include "../../Manager/Game/CollisionManager.h"
#include "../../Object/Character/Player.h"
#include "../../Object/Common/Animation.h"
#include "../../Collider/ColliderBox.h"
#include "../../Utility/UtilityCommon.h"
#include "ComponentAvilityStamp.h"
#include "ComponentAvilityTeleport.h"

ComponentAvilityStamp::ComponentAvilityStamp(Player& owner) :
	ComponentAvilityBase(owner)
{
	type_ = AvilityTypes::TYPE::STAMP;
	stopTime_ = 0.0f;
	inputEnableTime_ = INPUT_ENABLE_TIME;
	state_ = STATE::INPUT;
	update_ = std::bind(&ComponentAvilityStamp::UpdateInput, this);
	changeStateMap_.emplace(STATE::INPUT, std::bind(&ComponentAvilityStamp::ChangeStateInput, this));
	changeStateMap_.emplace(STATE::STOP, std::bind(&ComponentAvilityStamp::ChangeStateStop, this));
	changeStateMap_.emplace(STATE::ACTIVE, std::bind(&ComponentAvilityStamp::ChangeStateActive, this));
}

ComponentAvilityStamp::~ComponentAvilityStamp()
{
	if (attackCollider_)
	{
		attackCollider_->Delete();
		attackCollider_ = nullptr;
	}
}

void ComponentAvilityStamp::Create()
{	
	ComponentAvilityBase::Create();
	Init();
}

void ComponentAvilityStamp::Init()
{	
	// コライダーの登録
	attackCollider_ = owner_.CreateColliderClone();
	attackCollider_->ChangeTag(CollisionTags::TAG::PLAYER_AVILITY_STAMP);
	attackCollider_->SetIsActive(false);
	collisionManager_.Add(attackCollider_);
}

void ComponentAvilityStamp::Update()
{
	update_();
}

void ComponentAvilityStamp::Remove()
{
	if (attackCollider_)
	{
		attackCollider_->Delete();
		attackCollider_ = nullptr;
	}

	ComponentAvilityBase::Remove();

	// 所有者のコライダーの判定を有効にする
	owner_.SetColliderActive(true);
}

void ComponentAvilityStamp::UpdateInput()
{	
	// 地面にいる間は使用不可
	if (parameter_.isGround_)
	{
		inputEnableTime_ = INPUT_ENABLE_TIME;
		return;
	}
	
	// 入力受付時間の更新
	inputEnableTime_ -= sceneManager_.GetDeltaTime();

	// 入力受付
	if(inputManager_.IsTrgDown(InputManager::TYPE::AVILITY_STAMP, parameter_.padNo_) && inputEnableTime_ <= 0.0f && !parameter_.isAction_)
	{
		// 状態変更
		ChangeState(STATE::STOP);

		parameter_.isAction_ = true;
	}
}

void ComponentAvilityStamp::UpdateStop()
{
	stopTime_ -= sceneManager_.GetDeltaTime();
	if (stopTime_ <= 0.0f)
	{
		ChangeState(STATE::ACTIVE);
	}
}

void ComponentAvilityStamp::UpdateActive()
{
	// 地面に着地したか、もしくはキャラクターの入力処理が活動状態になったか
	if(parameter_.isGround_ || owner_.IsStateComponentActive(Player::STATE::ALIVE))
	{
		// 地面に着地したら状態を入力待ちにする
		ChangeState(STATE::INPUT);
	}
}

void ComponentAvilityStamp::ChangeState(const STATE state)
{
	state_ = state;
	changeStateMap_[state]();
}

void ComponentAvilityStamp::ChangeStateInput()
{
	update_ = std::bind(&ComponentAvilityStamp::UpdateInput, this);

	// アニメーションを待機にする
	owner_.GetAnimation().Play(Animation::TYPE::IDLE);

	// キャラクターの入力処理を有効にする
	owner_.SetStateComponentActive(Player::STATE::ALIVE, true);

	// 重力をもとに戻す
	parameter_.gravityPower_ -= ComponentAvilityStamp::ACC_GRAVITY;

	// 攻撃判定用コライダーを無効にする
	attackCollider_->SetIsActive(false);

	// 全てのアビリティを有効にする
	owner_.SetAllAvilityComponentActive(true);

	// 一部アビリティの初期化
	owner_.ResetAvilityComponent(AvilityTypes::TYPE::GRAVITYCONTROLL);
	owner_.ResetAvilityComponent(AvilityTypes::TYPE::SHOT);

	// 所有者のコライダーの判定を有効にする
	owner_.SetColliderActive(true);

	// 攻撃判定無効
	parameter_.isAction_ = false;
}

void ComponentAvilityStamp::ChangeStateStop()
{
	update_ = std::bind(&ComponentAvilityStamp::UpdateStop, this);
	
	// 一時停止時間
	stopTime_ = STOP_TIME;	
	
	// ジャンプ力を0にする
	owner_.SetJumpPow(0.0f);	
	
	// キャラクターの入力処理を無効にする
	owner_.SetStateComponentActive(Player::STATE::ALIVE, false);

	// キャラクターの重力を無効にする
	owner_.SetComponentActive("gravity", false);

	// 全てのアビリティを無効にする
	owner_.SetAllAvilityComponentActive(false);
	owner_.SetAvilityActive(AvilityTypes::TYPE::GRAVITYCONTROLL, true);	// 横方向に備えて重力は有効にしておく
	isActive_ = true;

	// アニメーション切り替えて停止
	owner_.GetAnimation().Play(Animation::TYPE::IDLE);
	owner_.GetAnimation().Stop();

	// 自身のコライダーの判定を無効にする
	owner_.SetColliderActive(false);

	// パラメータの初期化
	parameter_.jumpPow_ = 0.0f;
	parameter_.knockBackPower_ = Vector2F(0.0f, 0.0f);
	parameter_.shotVec_ = Vector2F(0.0f, 0.0f);
	parameter_.angle_ = UtilityCommon::GetGravityDirRadAngle(parameter_.gravityDir_);
}

void ComponentAvilityStamp::ChangeStateActive()
{
	update_ = std::bind(&ComponentAvilityStamp::UpdateActive, this);
	
	// 重力を加速
	parameter_.gravityPower_ += ACC_GRAVITY;

	// キャラクターの重力を有効にする
	owner_.SetComponentActive("gravity", true);

	// 攻撃判定用コライダーを有効にする
	attackCollider_->SetIsActive(true);
}