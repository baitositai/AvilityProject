#include "../../Object/Effect/EffectBase.h"
#include "OnHitEffectTeleport.h"

OnHitEffectTeleport::OnHitEffectTeleport(EffectBase& owner) :
	OnHitEffect(owner),
	owner_(owner)
{
	onHitMap_.emplace(CollisionTags::TAG::ENEMY_CLONE, [this](const std::weak_ptr<ColliderBase>& opponentCollider)
		{
			return OnHitEnemy(opponentCollider);
		});
}

OnHitEffectTeleport::~OnHitEffectTeleport()
{
}

void OnHitEffectTeleport::OnHitEnemy(const std::weak_ptr<ColliderBase>& opponentCollider)
{
	owner_.SetColliderActive(false);
}
