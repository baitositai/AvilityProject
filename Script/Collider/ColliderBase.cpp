#include "../Object/ActorBase.h"
#include "ColliderBase.h"

ColliderBase::ColliderBase(ActorBase& owner, const CollisionTags::TAG tag) :
	owner_(owner),
	tag_(tag)
{
	partnerTag_ = CollisionTags::TAG::NONE;
	type_ = ColliderType::TYPE::MAX;
	isHit_ = false;
	isDelete_ = false;
}

ColliderBase::~ColliderBase()
{
}

void ColliderBase::OnHit(const std::weak_ptr<ColliderBase>& opponentCollider)
{
	// 所有者のインスタンスを渡す
	owner_.OnHit(opponentCollider);
}

void ColliderBase::DebugDraw()
{
}
