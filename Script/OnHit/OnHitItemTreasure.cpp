#include "../Manager/Common/InputManager.h"
#include "../Object/Item/ItemTreasure.h"
#include "../Object/Character/Player.h"
#include "../Collider/ColliderBase.h"
#include "OnHitItemTreasure.h"

OnHitItemTreasure::OnHitItemTreasure(ItemTreasure& owner) :
	OnHitItemBase(owner),
	owner_(owner)
{
	onHitMap_.emplace(CollisionTags::TAG::ENEMY_BASE, [this](const std::weak_ptr<ColliderBase>& opponentCollider) { return OnHitEnemy(opponentCollider); });
	onHitMap_.emplace(CollisionTags::TAG::ENEMY_MAID, [this](const std::weak_ptr<ColliderBase>& opponentCollider) { return OnHitEnemy(opponentCollider); });
	onHitMap_.emplace(CollisionTags::TAG::BAMBOO, [this](const std::weak_ptr<ColliderBase>& opponentCollider) { return OnHitGimmick(opponentCollider); });
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
void OnHitItemTreasure::OnHitEnemy(const std::weak_ptr<ColliderBase>& opponentCollider)
{	
	// 投げられてる場合
	if (owner_.IsThrow())
	{
		owner_.ResetThrow();
	}
}

void OnHitItemTreasure::OnHitGimmick(const std::weak_ptr<ColliderBase>& opponentCollider)
{
	// 投げられてる場合
	if (owner_.IsThrow())
	{
		// 相手のオブジェクトを消す
		opponentCollider.lock()->GetOwner().Delete();
	}
}
