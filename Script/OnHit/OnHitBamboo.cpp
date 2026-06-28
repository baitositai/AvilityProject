#include "../Object/Gimmick/GimmickBamboo.h"
#include "OnHitBamboo.h"

OnHitBamboo::OnHitBamboo(GimmickBamboo& owner) :
	owner_(owner),
	OnHitBase(owner)
{

	onHitMap_.emplace(CollisionTags::TAG::PLAYER, [this](const std::weak_ptr<ColliderBase>& opponentCollider) { return OnHitPlayer(opponentCollider); });
	onHitMap_.emplace(CollisionTags::TAG::PLAYER_ATTACK_NORMAL, [this](const std::weak_ptr<ColliderBase>& opponentCollider) { return OnHitPlayerAttack(opponentCollider); });
	onHitMap_.emplace(CollisionTags::TAG::PLAYER_AVILITY_SHOT, [this](const std::weak_ptr<ColliderBase>& opponentCollider) { return OnHitPlayerAttack(opponentCollider); });
	onHitMap_.emplace(CollisionTags::TAG::PLAYER_AVILITY_STAMP, [this](const std::weak_ptr<ColliderBase>& opponentCollider) { return OnHitPlayerAttack(opponentCollider); });
	onHitMap_.emplace(CollisionTags::TAG::TELEPORT_EXIT, [this](const std::weak_ptr<ColliderBase>& opponentCollider) { return OnHitPlayerAttack(opponentCollider); });
}

OnHitBamboo::~OnHitBamboo()
{
}

void OnHitBamboo::OnHitPlayer(const std::weak_ptr<ColliderBase>& opponentCollider)
{
	// çÌèúèàóù
	owner_.Delete();
}

void OnHitBamboo::OnHitPlayerAttack(const std::weak_ptr<ColliderBase>& opponentCollider)
{
	// çÌèúèàóù
	owner_.Delete();
}