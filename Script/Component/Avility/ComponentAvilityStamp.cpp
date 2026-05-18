#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Common/InputManager.h"
#include "../../Manager/Game/CollisionManager.h"
#include "../../Object/Character/Player.h"
#include "../../Object/Common/Animation.h"
#include "../../Collider/ColliderBox.h"
#include "ComponentAvilityStamp.h"

ComponentAvilityStamp::ComponentAvilityStamp(Player& owner) :
	ComponentAvilityBase(owner)
{
	abilitySlot_ = ABILITY_SLOT::SECOND;
	type_ = AvilityTypes::TYPE::STAMP;
	stopTime_ = 0.0f;
	inputEnableTime_ = INPUT_ENABLE_TIME;
	state_ = STATE::INPUT;
	update_ = std::bind(&ComponentAvilityStamp::UpdateInput, this);
	stateChangeMap_.emplace(STATE::INPUT, std::bind(&ComponentAvilityStamp::ChangeStateInput, this));
	stateChangeMap_.emplace(STATE::STOP, std::bind(&ComponentAvilityStamp::ChangeStateStop, this));
	stateChangeMap_.emplace(STATE::ACTIVE, std::bind(&ComponentAvilityStamp::ChangeStateActive, this));

	// コライダーの登録
	attackCollider_ = owner_.CreateColliderClone();
	attackCollider_->ChangeTag(CollisionTags::TAG::PLAYER_AVILITY_STAMP);
	attackCollider_->SetIsActive(false);
	CollisionManager::GetInstance().Add(attackCollider_);

	// 攻撃力の加算
	owner_.AddAttackPower(ADD_ATTACK_POWER);
}

ComponentAvilityStamp::~ComponentAvilityStamp()
{

}

void ComponentAvilityStamp::Update()
{
	update_();
}

void ComponentAvilityStamp::Remove()
{
	// コライダーの削除 
	if(attackCollider_)
	{
		attackCollider_->SetDelete();
	}

	// 攻撃力を戻す
	owner_.AddAttackPower(-ADD_ATTACK_POWER);

	// 所有者のコライダーの判定を有効にする
	owner_.SetColliderActive(true);
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
	// 地面に着地したか、もしくはキャラクターの入力処理が活動状態になったか
	if(owner_.IsGround() || owner_.IsStateComponentActive(Player::STATE::ALIVE))
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

	// キャラクターの入力処理を有効にする
	owner_.SetStateComponentActive(Player::STATE::ALIVE, true);

	// 重力をもとに戻す
	owner_.AddGravityPower(-ComponentAvilityStamp::ACC_GRAVITY);

	// 攻撃判定用コライダーを無効にする
	attackCollider_->SetIsActive(false);

	// 所有者のコライダーの判定を有効にする
	owner_.SetColliderActive(true);
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

	// 自身のコライダーの判定を無効にする
	owner_.SetColliderActive(false);
}

void ComponentAvilityStamp::ChangeStateActive()
{
	update_ = std::bind(&ComponentAvilityStamp::UpdateActive, this);
	
	// 重力を加速
	owner_.AddGravityPower(ACC_GRAVITY);

	// キャラクターの重力を有効にする
	owner_.SetComponentActive("gravity", true);

	// 攻撃判定用コライダーを有効にする
	attackCollider_->SetIsActive(true);
}