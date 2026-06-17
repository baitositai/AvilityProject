#include "../Object/Item/ItemMoney.h"
#include "OnHitItemMoney.h"

OnHitItemMoney::OnHitItemMoney(ItemMoney& owner) :
	OnHitItemBase(owner),
	owner_(owner)
{
}

OnHitItemMoney::~OnHitItemMoney()
{
}

void OnHitItemMoney::OnHitPlayer(const std::weak_ptr<ColliderBase>& opponentCollider)
{
	owner_.Delete();
}