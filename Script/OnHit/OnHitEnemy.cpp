#include "../../Collider/ColliderBase.h"
#include "../../Object/Character/Enemy/EnemyBase.h"
#include "OnHitEnemy.h"

OnHitEnemy::OnHitEnemy(EnemyBase& owner):
	owner_(owner),
	OnHitCharacterBase(owner)
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
			return OnHitPlayerAttack(opponentCollider);
		});
}

OnHitEnemy::~OnHitEnemy()
{
}

void OnHitEnemy::OnHitPlayerAttack(const std::weak_ptr<ColliderBase>& opponentCollider)
{
	// 共通処理
	OnHitAttack(opponentCollider);

	// 相手コライダーの判定を無効化
	opponentCollider.lock()->SetIsActive(false);
}

void OnHitEnemy::OnHitPlayerAvilityStamp(const std::weak_ptr<ColliderBase>& opponentCollider)
{
	// ノックバック処理
	KnockBack(opponentCollider, KNOCK_BACK_FORCE);

	// 相手コライダーの判定を無効化
	opponentCollider.lock()->SetIsActive(false);
}
