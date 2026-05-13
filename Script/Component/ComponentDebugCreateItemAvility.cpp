#include "../../Manager/Common/InputManager.h"
#include "ComponentDebugCreateItemAvility.h"

ComponentDebugCreateItemAvility::ComponentDebugCreateItemAvility(ActorBase& owner) :
	ComponentBase(&owner),
	inputManager_(InputManager::GetInstance())
{
}

ComponentDebugCreateItemAvility::~ComponentDebugCreateItemAvility()
{
}

void ComponentDebugCreateItemAvility::Update()
{

}
