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
	// íœ
	owner_.Delete();
}