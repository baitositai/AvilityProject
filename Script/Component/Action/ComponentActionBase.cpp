#include "../../Object/Character/CharacterBase.h"
#include "ComponentActionBase.h"

ComponentActionBase::ComponentActionBase(CharacterBase& owner) :
	ComponentBase(&owner),
	owner_(owner)

{
}

ComponentActionBase::~ComponentActionBase()
{
}
