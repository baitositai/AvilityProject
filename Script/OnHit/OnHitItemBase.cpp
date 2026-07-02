#include "../Manager/Common/InputManager.h"
#include "../Object/Character/Player.h"
#include "../Object/Item/ItemBase.h"
#include "../Collider/ColliderBase.h"
#include "OnHitItemBase.h"

OnHitItemBase::OnHitItemBase(ItemBase& owner) :
	owner_(owner),
	inputManager_(InputManager::GetInstance()),
	OnHitBase(owner)
{

	onHitMap_.emplace(CollisionTags::TAG::PLAYER, [this](const std::weak_ptr<ColliderBase>& opponentCollider) { return OnHitPlayer(opponentCollider); });
	onHitMap_.emplace(CollisionTags::TAG::ENEMY_MAID, [this](const std::weak_ptr<ColliderBase>& opponentCollider) { return OnHitEnemyMaid(opponentCollider); });
}

OnHitItemBase::~OnHitItemBase()
{
}

void OnHitItemBase::OnHitPlayer(const std::weak_ptr<ColliderBase>& opponentCollider)
{
	// 書き換え可能な所有者を取得
	auto* player = dynamic_cast<Player*>(&opponentCollider.lock()->GetOwner());

	// キャストが成功した場合
	if (player)
	{
		if (inputManager_.IsTrgDown(InputManager::TYPE::PLAYER_GET_ITEM, player->GetParameter().padNo_))
		{
			// 衝突者を所有者として取得
			owner_.Delete();
		}
	}
}

void OnHitItemBase::OnHitEnemyMaid(const std::weak_ptr<ColliderBase>& opponentCollider)
{
	// 衝突者を所有者として取得
	owner_.Delete();
}