#include "../../Manager/Common/InputManager.h"
#include "../../Manager/Game/ItemManager.h"
#include "../../Object/Item/ItemAvility.h"
#include "../../Object/ActorBase.h"
#include "Avility/AvilityList.h"
#include "ComponentDebugCreateItemAvility.h"

ComponentDebugCreateItemAvility::ComponentDebugCreateItemAvility(ActorBase& owner) :
	ComponentBase(&owner),
	inputManager_(InputManager::GetInstance())
{
	type_ = 0;
}

ComponentDebugCreateItemAvility::~ComponentDebugCreateItemAvility()
{
}

void ComponentDebugCreateItemAvility::Update()
{
	if (inputManager_.IsTrgDown(InputManager::TYPE::DEBUG_CREATE_ITEM_AVILITY))
	{
		ItemAvility::Parameter parameter = {};
		parameter.type = static_cast<AVILITY_TYPE>(type_);
		parameter.pos = owner_->GetParameter()->pos;
		parameter.hitRadius = 20.0f;
		parameter.gravityPower = 9.8f;
		parameter.gravityDir = ActorBase::DIR::DOWN;

		std::vector<std::string> componentNameList = { "gravity" };
		ItemManager::GetInstance().Add(std::make_unique<ItemAvility>(parameter, componentNameList));
	}
	else if (inputManager_.IsTrgDown(InputManager::TYPE::DEBUG_SELECT_RIGHT_ITEM_AVILITY))
	{
	}
	else if (inputManager_.IsTrgDown(InputManager::TYPE::DEBUG_SELECT_LEFT_ITEM_AVILITY))
	{
	}
}
