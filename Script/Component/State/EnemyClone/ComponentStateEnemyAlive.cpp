#include <DxLib.h>
#include "../../Object/Character/CharacterBase.h"
#include "ComponentStateEnemyAlive.h"

ComponentStateEnemyAlive::ComponentStateEnemyAlive(CharacterBase& owner) :
	ComponentBase(&owner),
	owner_(owner)
{
}

ComponentStateEnemyAlive::~ComponentStateEnemyAlive()
{
}

void ComponentStateEnemyAlive::Update()
{
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		owner_.SetMoveAmount(Vector2F(3.0f, 0.0f));
	}
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		owner_.SetMoveAmount(Vector2F(-3.0f, 0.0f));
	}
	if (CheckHitKey(KEY_INPUT_UP))
	{
		owner_.SetMoveAmount(Vector2F(0.0f, -3.0f));
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		owner_.SetMoveAmount(Vector2F(0.0f, 3.0f));
	}
}
