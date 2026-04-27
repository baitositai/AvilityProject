#include "../Manager/Game/StageManager.h"
#include "../../Manager/Common/InputManager.h"
#include "../../Object/Character/Player.h"
#include "ComponentAvilityBase.h"

ComponentAvilityBase::ComponentAvilityBase(Player& owner) :
	owner_(owner),
	stageManager_(StageManager::GetInstance()),
	inputManager_(InputManager::GetInstance()),
	ComponentBase(&owner)
{
}

ComponentAvilityBase::~ComponentAvilityBase()
{
}

void ComponentAvilityBase::Update()
{
}
