#include "../../Object/Item/ItemFood.h"
#include "../../Object/Character/Enemy/EnemyMaid.h"
#include "../../Collider/ColliderBase.h"
#include "OnHitEnemyMaid.h"

OnHitEnemyMaid::OnHitEnemyMaid(EnemyMaid& owner) :
	OnHitEnemy(owner),
	owner_(owner)
{
	onHitMap_.emplace(CollisionTags::TAG::PLAYER_ATTACK_NORMAL, [this](const std::weak_ptr<ColliderBase>& opponentCollider)
		{
			return OnHitPlayerAttack(opponentCollider);
		});
	onHitMap_.emplace(CollisionTags::TAG::PLAYER_AVILITY_STAMP, [this](const std::weak_ptr<ColliderBase>& opponentCollider)
		{
			return OnHitPlayerAvilityStamp(opponentCollider);
		});
	onHitMap_.emplace(CollisionTags::TAG::PLAYER_AVILITY_SHOT, [this](const std::weak_ptr<ColliderBase>& opponentCollider)
		{
			return OnHitPlayerAvilityShot(opponentCollider);
		});
	onHitMap_.emplace(CollisionTags::TAG::AIRSLASH, [this](const std::weak_ptr<ColliderBase>& opponentCollider)
		{
			return OnHitPlayerAttack(opponentCollider);
		});
	onHitMap_.emplace(CollisionTags::TAG::TELEPORT_EXIT, [this](const std::weak_ptr<ColliderBase>& opponentCollider)
		{
			return OnHitPlayerAttack(opponentCollider);
		});
	onHitMap_.emplace(CollisionTags::TAG::ITEM_FOOD, [this](const std::weak_ptr<ColliderBase>& opponentCollider)
		{
			return OnHitItemFood(opponentCollider);
		});
}

OnHitEnemyMaid::~OnHitEnemyMaid()
{
}

void OnHitEnemyMaid::Update(const std::weak_ptr<ColliderBase>& opponentCollider)
{
	// 自身のタグ別に処理を呼び分ける
	switch (opponentCollider.lock()->GetPartnerTag())
	{
	case CollisionTags::TAG::ENEMY_MAID:
		// 基底クラスの共通処理
		OnHitCharacterBase::Update(opponentCollider);
		break;

	case CollisionTags::TAG::ENEMY_VIEW:
		// 現状プレイヤーだけ
		OnHitEnemyViewToPlayer(opponentCollider);
		break;

	default:
		break;
	}
}

void OnHitEnemyMaid::OnHitItemFood(const std::weak_ptr<ColliderBase>& opponentCollider)
{
    // 衝突相手の所有者をキャストしてアイテムのインスタンスを取得
    const auto& item = dynamic_cast<const ItemBase*>(&opponentCollider.lock()->GetOwner());

    // アイテムのアビリティを取得
    const auto& itemFood = dynamic_cast<const ItemFood*>(item);

    // アイテムの種類を獲得
    owner_.Heal(itemFood->GetParameter().heal_);

	// 取得回数追加
	owner_.GetParameter().hitFoodCount_++;
}