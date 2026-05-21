#include "../Object/Effect/EffectBase.h"
#include "OnHitEffect.h"

OnHitEffect::OnHitEffect(EffectBase& owner) :
	OnHitBase(owner),
	owner_(owner)
{
	onHitMap_.emplace(CollisionTags::TAG::ENEMY_CLONE, [this](const std::weak_ptr<ColliderBase>& opponentCollider) { return OnHitEnemy(opponentCollider); });
}

OnHitEffect::~OnHitEffect()
{
}

void OnHitEffect::OnHitEnemy(const std::weak_ptr<ColliderBase>& opponentCollider)
{
	owner_.Delete();
}