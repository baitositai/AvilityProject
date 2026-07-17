#include "../Manager/Common/SoundManager.h"
#include "../Manager/Common/ScoreManager.h"
#include "../Manager/Common/InputManager.h"
#include "../Manager/Common/SpriteEffectManager.h"	
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
	onHitMap_.emplace(CollisionTags::TAG::TARGET, [this](const std::weak_ptr<ColliderBase>& opponentCollider) { return OnHitTarget(opponentCollider); });
	onHitMap_.emplace(CollisionTags::TAG::TRAIN, [this](const std::weak_ptr<ColliderBase>& opponentCollider) { return OnHitTrain(opponentCollider); });
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

			// 効果音再生
			soundManager_.PlaySe(SoundType::SE::GET_TREASURE);
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

void OnHitItemTreasure::OnHitTarget(const std::weak_ptr<ColliderBase>& opponentCollider)
{
	// 投げられてる場合
	if (owner_.IsThrow())
	{
		// 相手のオブジェクトを消す
		opponentCollider.lock()->GetOwner().Delete();
	}
}

void OnHitItemTreasure::OnHitTrain(const std::weak_ptr<ColliderBase>& opponentCollider)
{
	// 投げられてる場合
	if (owner_.IsThrow())
	{
		// エフェクトの再生
		SpriteEffectManager::CreateParameter parameter;
		parameter.pos = owner_.GetParameter().pos_;
		parameter.resourceKey = "treasureThrowHit";
		parameter.scale = 1.5f;
		parameter.animationSpeed = 0.3f;
		SpriteEffectManager::GetInstance().Create(parameter);

		// スコアを加算
		ScoreManager::GetInstance().AddScore(owner_.GetParameter().amount_);

		// 自身を消す
		owner_.Delete();
	}
}
