#include "../Manager/Common/InputManager.h"
#include "../Object/Item/ItemTreasure.h"
#include "../Object/Character/Player.h"
#include "../Collider/ColliderBase.h"
#include "OnHitItemTreasure.h"

OnHitItemTreasure::OnHitItemTreasure(ItemTreasure& owner) :
	OnHitItemBase(owner),
	owner_(owner)
{
}

OnHitItemTreasure::~OnHitItemTreasure()
{
}

void OnHitItemTreasure::OnHitPlayer(const std::weak_ptr<ColliderBase>& opponentCollider)
{	
	// 書き換え可能な所有者を取得
	auto* player = dynamic_cast<Player*>(&opponentCollider.lock()->GetOwner());

	// キャストが成功した場合
	if (player)
	{	
		if (inputManager_.IsTrgDown(InputManager::TYPE::PLAYER_GET_ITEM, player->GetParameter().padNo_))
		{
			// 衝突者を所有者として取得
			owner_.FollowPlayer(*player);
		}
	}
}