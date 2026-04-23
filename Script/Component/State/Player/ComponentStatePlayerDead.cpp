#include "../../../Object/Character/Player.h"
#include "ComponentStatePlayerDead.h"

ComponentStatePlayerDead::ComponentStatePlayerDead(Player& owner) :
	ComponentCharacterStateBase(owner)
{
}

ComponentStatePlayerDead::~ComponentStatePlayerDead()
{
}

void ComponentStatePlayerDead::Update()
{
}
