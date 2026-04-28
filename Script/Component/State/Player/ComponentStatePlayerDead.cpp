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
	owner_->SetMoveAmount(Vector2F(0.0f,0.0f));
}
