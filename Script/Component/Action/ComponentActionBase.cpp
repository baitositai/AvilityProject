#include "../../Object/Character/CharacterBase.h"
#include "ComponentActionBase.h"

ComponentActionBase::ComponentActionBase(CharacterBase& owner) :
	ComponentBase(&owner)

{
}

ComponentActionBase::~ComponentActionBase()
{
}
