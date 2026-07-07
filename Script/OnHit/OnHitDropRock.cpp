#include "../Object/Gimmick/GimmickDropRock.h"
#include "OnHitDropRock.h"

OnHitDropRock::OnHitDropRock(GimmickDropRock& owner):
	OnHitBase(owner),
	owner_(owner)
{
	onHitMap_.emplace(CollisionTags::TAG::PLAYER, [this](const std::weak_ptr<ColliderBase>& opponentCollider) { return OnHitPlayer(opponentCollider); });
	onHitMap_.emplace(CollisionTags::TAG::STAGE,[this](const std::weak_ptr<ColliderBase>& opponentCollider) { return OnHitPlayer(opponentCollider); });
}

OnHitDropRock::~OnHitDropRock()
{
}

void OnHitDropRock::OnHitPlayer(const std::weak_ptr<ColliderBase>& opponentCollider)
{
	// çÌèúèàóù
	owner_.Delete();
}