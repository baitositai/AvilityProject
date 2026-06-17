#include "../../Manager/Common/InputManager.h"
#include "../Object/Item/ItemBase.h"
#include "OnHitItemBase.h"

OnHitItemBase::OnHitItemBase(ItemBase& owner) :
	owner_(owner),
	inputManager_(InputManager::GetInstance()),
	OnHitBase(owner)
{

	onHitMap_.emplace(CollisionTags::TAG::PLAYER, [this](const std::weak_ptr<ColliderBase>& opponentCollider) { return OnHitPlayer(opponentCollider); });
}

OnHitItemBase::~OnHitItemBase()
{
}

void OnHitItemBase::OnHitPlayer(const std::weak_ptr<ColliderBase>& opponentCollider)
{
    if (inputManager_.IsTrgDown(InputManager::TYPE::PLAYER_GET_ITEM))
    {
		// çÌèúÇ∑ÇÈ
		owner_.Delete();
    }
}