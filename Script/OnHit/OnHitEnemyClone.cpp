#include "../../Collider/ColliderBase.h"
#include "../../Object/Character/CharacterBase.h"
#include "../../Object/Character/Enemy/EnemyClone.h"
#include "OnHitEnemyClone.h"
OnHitEnemyClone::OnHitEnemyClone(EnemyClone& owner):
	owner_(owner),
	OnHitCharacterBase(owner)
{
	onHitMap_.emplace(CollisionTags::TAG::PLAYER_ATTACK_NORMAL, [this](const std::weak_ptr<ColliderBase>& opponentCollider)
		{
			return OnHitPlayerAttack(opponentCollider);
		});
}

OnHitEnemyClone::~OnHitEnemyClone()
{
}

void OnHitEnemyClone::OnHitPlayerAttack(const std::weak_ptr<ColliderBase>& opponentCollider)
{
	OnHitAttack(opponentCollider);

	// コライダーの判定を無効化
	opponentCollider.lock()->SetIsActive(false);
}
