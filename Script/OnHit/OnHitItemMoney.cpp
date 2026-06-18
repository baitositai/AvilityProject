#include "../Object/Item/ItemMoney.h"
#include "../Manager/Common/ScoreManager.h"
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
	ScoreManager::GetInstance().AddScore(owner_.GetParameter().amount_);
	owner_.Delete();
}