#include "../Manager/Common/SoundManager.h"
#include "../Object/Gimmick/GimmickTarget.h"
#include "OnHitTarget.h"

OnHitTarget::OnHitTarget(GimmickTarget& owner) :
	OnHitBase(owner),
	owner_(owner)
{
}

OnHitTarget::~OnHitTarget()
{
}

void OnHitTarget::Update(const std::weak_ptr<ColliderBase>& opponentCollider)
{
	// Œø‰Ê‰¹Ä¶
	soundManager_.PlaySe(SoundType::SE::PLAYER_ATTACK_HIT);
	soundManager_.PlaySe(SoundType::SE::TARGET_DESTROY);

	// íœ
	owner_.Delete();
}