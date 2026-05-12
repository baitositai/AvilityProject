#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Common/InputManager.h"
#include "../../Object/Character/Player.h"
#include "../../Object/Common/Animation.h"
#include "ComponentAvilityStamp.h"

ComponentAvilityStamp::ComponentAvilityStamp(Player& owner) :
	ComponentAvilityBase(owner)
{
	stopTime_ = 0.0f;
	inputEnableTime_ = INPUT_ENABLE_TIME;
	gravity_ = 0.0f;
	state_ = STATE::INPUT;
	update_ = std::bind(&ComponentAvilityStamp::UpdateInput, this);
	stateChangeMap_.emplace(STATE::INPUT, std::bind(&ComponentAvilityStamp::ChangeStateInput, this));
	stateChangeMap_.emplace(STATE::STOP, std::bind(&ComponentAvilityStamp::ChangeStateStop, this));
	stateChangeMap_.emplace(STATE::ACTIVE, std::bind(&ComponentAvilityStamp::ChangeStateActive, this));
}

ComponentAvilityStamp::~ComponentAvilityStamp()
{
}

void ComponentAvilityStamp::Update()
{
	update_();
}

void ComponentAvilityStamp::UpdateInput()
{	
	// 地面にいる間は使用不可
	if (owner_.IsGround())
	{
		inputEnableTime_ = INPUT_ENABLE_TIME;
		return;
	}
	
	// 入力受付時間の更新
	inputEnableTime_ -= sceneManager_.GetDeltaTime();

	// 入力受付
	if(inputManager_.IsTrgDown(InputManager::TYPE::AVILITY_STAMP) && inputEnableTime_ <= 0.0f)
	{
		// 状態変更
		ChangeState(STATE::STOP);
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
	if(owner_.IsGround())
	{
		// 地面に着地したら状態を入力待ちにする
		ChangeState(STATE::INPUT);
	}
}

void ComponentAvilityStamp::ChangeState(const STATE state)
{
	state_ = state;
	stateChangeMap_[state]();
}

void ComponentAvilityStamp::ChangeStateInput()
{
	update_ = std::bind(&ComponentAvilityStamp::UpdateInput, this);

	// アニメーションを待機にする
	owner_.GetAnimation().Play(Animation::TYPE::IDLE);

	// 重力をもとに戻す
	owner_.SetGravityPower(gravity_);

	// キャラクターの入力処理を有効にする
	owner_.SetStateComponentActive(Player::STATE::ALIVE, true);

	// 入力受付時間を指定
	inputEnableTime_ = INPUT_ENABLE_TIME;
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

	// アニメーション切り替えて停止
	owner_.GetAnimation().Play(Animation::TYPE::IDLE);
	owner_.GetAnimation().Stop();
}

void ComponentAvilityStamp::ChangeStateActive()
{
	update_ = std::bind(&ComponentAvilityStamp::UpdateActive, this);
	
	// 重力を加速
	gravity_ = owner_.GetParameter()->gravityPower;
	owner_.SetGravityPower(gravity_ + ACC_GRAVITY);

	// キャラクターの重力を有効にする
	owner_.SetComponentActive("gravity", true);
}