#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Common/InputManager.h"
#include "../../Object/Character/Player.h"
#include "../../Utility/UtilityCommon.h"
#include "ComponentAvilityGravity.h"

ComponentAvilityGravity::ComponentAvilityGravity(Player& owner) :
	ComponentAvilityBase(owner)
{
	coolTime_ = 0.0f;
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

void ComponentAvilityGravity::ProcessGravity()
{
	if (inputManager_.IsTrgDown(InputManager::TYPE::AVILITY_GRAVITY_RIGHT))
	{
		owner_.SetGravityDir(ActorBase::DIR::RIGHT);
		owner_.SetAngle(UtilityCommon::Deg2RadF(270.0f));
		coolTime_ = COOL_TIME;
	}
	else if (inputManager_.IsTrgDown(InputManager::TYPE::AVILITY_GRAVITY_LEFT))
	{
		owner_.SetGravityDir(ActorBase::DIR::LEFT);
		owner_.SetAngle(UtilityCommon::Deg2RadF(90.0f));
		coolTime_ = COOL_TIME;
	}
	else if (inputManager_.IsTrgDown(InputManager::TYPE::AVILITY_GRAVITY_UP))
	{
		owner_.SetGravityDir(ActorBase::DIR::UP);
		owner_.SetAngle(UtilityCommon::Deg2RadF(180.0f));
		coolTime_ = COOL_TIME;
	}
	else if (inputManager_.IsTrgDown(InputManager::TYPE::AVILITY_GRAVITY_DOWN))
	{
		owner_.SetGravityDir(ActorBase::DIR::DOWN);
		owner_.SetAngle(UtilityCommon::Deg2RadF(0.0f));
		coolTime_ = COOL_TIME;
	}
}
