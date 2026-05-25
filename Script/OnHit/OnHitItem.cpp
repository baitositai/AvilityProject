#include "../Object/Item/ItemBase.h"
#include "OnHitItem.h"

OnHitItem::OnHitItem(ItemBase& owner) :
	owner_(owner),
	OnHitBase(owner)
{

	onHitMap_.emplace(CollisionTags::TAG::PLAYER, [this](const std::weak_ptr<ColliderBase>& opponentCollider) { return OnHitPlayer(opponentCollider); });
}

OnHitItem::~OnHitItem()
{
}

void OnHitItem::OnHitPlayer(const std::weak_ptr<ColliderBase>& opponentCollider)
{
	// çÌèúÇ∑ÇÈ
	owner_.Delete();
}