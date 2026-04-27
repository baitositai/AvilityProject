#include "../Object/Character/Enemy/EnemyClone.h"
#include "OnHitEnemyClone.h"
OnHitEnemyClone::OnHitEnemyClone(EnemyClone& owner):
	owner_(owner),
	OnHitCharacterBase(owner)
{
}
OnHitEnemyClone::~OnHitEnemyClone()
{
}
