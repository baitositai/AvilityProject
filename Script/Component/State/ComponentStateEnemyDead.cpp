#include "../../Object/Character/Enemy/EnemyBase.h"
#include "ComponentStateEnemyDead.h"

ComponentStateEnemyDead::ComponentStateEnemyDead(EnemyBase& owner) :
	ComponentCharacterStateBase(owner),
	owner_(owner)
{
}

ComponentStateEnemyDead::~ComponentStateEnemyDead()
{
}

void ComponentStateEnemyDead::Init()
{
}

void ComponentStateEnemyDead::Update()
{
	// 死亡アニメーションが終了した場合
	if (owner_.GetAnimation().GetType() == Animation::TYPE::DEAD &&
		!owner_.GetAnimation().IsPlay())
	{
		// アイテムのドロップ
		owner_.DropItem();

		// 所有者を消す
		owner_.Delete();
	}
}
