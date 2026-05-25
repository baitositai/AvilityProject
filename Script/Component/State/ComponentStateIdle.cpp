#include "../../Object/Character/CharacterBase.h"
#include "ComponentStateIdle.h"

ComponentStateIdle::ComponentStateIdle(CharacterBase& owner) :
	ComponentCharacterStateBase(owner)
{
}

ComponentStateIdle::~ComponentStateIdle()
{
}
