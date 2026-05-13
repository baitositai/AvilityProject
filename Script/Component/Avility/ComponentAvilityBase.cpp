#include "../../Manager/Common/InputManager.h"
#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Game/StageManager.h"
#include "../../Object/Character/Player.h"
#include "ComponentAvilityBase.h"

ComponentAvilityBase::ComponentAvilityBase(Player& owner) :
	owner_(owner),
	stageManager_(StageManager::GetInstance()),
	sceneManager_(SceneManager::GetInstance()),
	inputManager_(InputManager::GetInstance()),
	ComponentBase(&owner)
{
	abilitySlot_ = ABILITY_SLOT::MAX;
}

ComponentAvilityBase::~ComponentAvilityBase()
{
}

void ComponentAvilityBase::Update()
{
}
