#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Common/InputManager.h"
#include "../../Object/Character/Player.h"
#include "../../Utility/UtilityCommon.h"
#include "ComponentAvilityGravity.h"

ComponentAvilityGravity::ComponentAvilityGravity(Player& owner) :
	ComponentAvilityBase(owner)
{
	coolTime_ = 0.0f;
	abilitySlot_ = ABILITY_SLOT::FIRST;
	type_ = AvilityTypes::TYPE::GRAVITY;
}

ComponentAvilityGravity::~ComponentAvilityGravity()
{

}

void ComponentAvilityGravity::Update()
{
	// クールタイムが0以下の場合
	if (coolTime_ > 0.0f)
	{
		coolTime_ -= sceneManager_.GetDeltaTime();
		return;
	}

	// 入力処理
	ProcessGravity();
}

void ComponentAvilityGravity::Remove()
{
	// 重力方向を下に戻す
	if (owner_.GetParameter()->gravityDir != ActorBase::DIR::DOWN)
	{
		owner_.SetGravityDir(ActorBase::DIR::DOWN);
		owner_.SetIsGround(false);
	}
}

void ComponentAvilityGravity::ProcessGravity()
{
	if (inputManager_.IsTrgDown(InputManager::TYPE::AVILITY_GRAVITY_RIGHT))
	{
		owner_.SetGravityDir(ActorBase::DIR::RIGHT);
		owner_.SetAngle(UtilityCommon::Deg2RadF(270.0f));
		coolTime_ = COOL_TIME;
		owner_.SetIsGround(false);
	}
	else if (inputManager_.IsTrgDown(InputManager::TYPE::AVILITY_GRAVITY_LEFT))
	{
		owner_.SetGravityDir(ActorBase::DIR::LEFT);
		owner_.SetAngle(UtilityCommon::Deg2RadF(90.0f));
		coolTime_ = COOL_TIME;
		owner_.SetIsGround(false);
	}
	else if (inputManager_.IsTrgDown(InputManager::TYPE::AVILITY_GRAVITY_UP))
	{
		owner_.SetGravityDir(ActorBase::DIR::UP);
		owner_.SetAngle(UtilityCommon::Deg2RadF(180.0f));
		coolTime_ = COOL_TIME;
		owner_.SetIsGround(false);
	}
	else if (inputManager_.IsTrgDown(InputManager::TYPE::AVILITY_GRAVITY_DOWN))
	{
		owner_.SetGravityDir(ActorBase::DIR::DOWN);
		owner_.SetAngle(UtilityCommon::Deg2RadF(0.0f));
		coolTime_ = COOL_TIME;
		owner_.SetIsGround(false);
	}
}
