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
	// ˆÚ“®—Ê‚Ì‰Šú‰»
	Vector2F moveAmount = {};
	moveAmount.y = owner_.GetParameter()->moveAmount.y;
	float moveSpeed = owner_.GetParameter()->moveSpeed;

	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		moveAmount.x += moveSpeed;
	}
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		moveAmount.x -= moveSpeed;
	}
	if (CheckHitKey(KEY_INPUT_UP))
	{
		moveAmount.y -= moveSpeed;
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		moveAmount.y += moveSpeed;
	}

	owner_.SetMoveAmount(moveAmount);
}
