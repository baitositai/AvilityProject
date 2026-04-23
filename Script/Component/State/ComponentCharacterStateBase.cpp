#include "../../Object/Character/CharacterBase.h"
#include "ComponentCharacterStateBase.h"

ComponentCharacterStateBase::ComponentCharacterStateBase(CharacterBase& owner) :
	ComponentBase(&owner)
{
}

ComponentCharacterStateBase::~ComponentCharacterStateBase()
{
}