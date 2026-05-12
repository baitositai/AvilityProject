#include "../../Object/Character/CharacterBase.h"
#include "ComponentStateDummy.h"

ComponentStateDummy::ComponentStateDummy(CharacterBase& owner) :
	ComponentCharacterStateBase(owner)
{
}

ComponentStateDummy::~ComponentStateDummy()
{
}
