#include "../Object/Gimmick/GimmickTreasureChest.h"
#include "../Manager/Game/ItemManager.h"
#include "../Collider/ColliderBase.h"
#include "OnHitTreasureChest.h"

OnHitTreasureChest::OnHitTreasureChest(GimmickTreasureChest& owner) :
	OnHitBase(owner),
	owner_(owner)
{
}

OnHitTreasureChest::~OnHitTreasureChest()
{
}

void OnHitTreasureChest::Update(const std::weak_ptr<ColliderBase>& opponentCollider)
{
	// 自身の衝突判定を消す
	owner_.SetColliderActive(false);

	// アニメーションを再生（ループしない）
	owner_.GetAnimation().Play(Animation::TYPE::WALK, false);

	// 宝箱用のアイテム生成
	ItemManager::GetInstance().CreateTreasureChestItems(owner_.GetParameter().pos_);
}
