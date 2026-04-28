#include "../../Object/Character/CharacterBase.h"
#include "ComponentStateDead.h"

ComponentStateDead::ComponentStateDead(CharacterBase& owner) :
	ComponentCharacterStateBase(owner)
{
}

ComponentStateDead::~ComponentStateDead()
{
}

void ComponentStateDead::Update()
{
	owner_->SetMoveAmount(Vector2F());
}
