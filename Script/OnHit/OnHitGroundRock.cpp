#include "../Object/Gimmick/GimmickGroundRock.h"
#include "OnHitGroundRock.h"

OnHitGroundRock::OnHitGroundRock(GimmickGroundRock& owner):
	OnHitBase(owner),
	owner_(owner)
{
	onHitMap_.emplace(CollisionTags::TAG::PLAYER, [this](const std::weak_ptr<ColliderBase>& opponentCollider) { return OnHitPlayer(opponentCollider); });
}

OnHitGroundRock::~OnHitGroundRock()
{
}
void OnHitGroundRock::OnHitPlayer(const std::weak_ptr<ColliderBase>& opponentCollider)
{
	//çÌèúèàóù
	owner_.Delete();
}