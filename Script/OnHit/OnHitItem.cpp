#include "../Object/Item/ItemBase.h"
#include "OnHitItem.h"

OnHitItem::OnHitItem(ItemBase& owner) :
	owner_(owner),
	OnHitBase(owner)
{
}

OnHitItem::~OnHitItem()
{
}

void OnHitItem::OnHitPlayer(const std::weak_ptr<ColliderBase>& opponentCollider)
{
	// çÌèúÇ∑ÇÈ
	owner_.Delete();
}