#include "../Object/ActorBase.h"
#include "ColliderCircle.h"

ColliderCircle::ColliderCircle(ActorBase& owner, const CollisionTags::TAG tag, const float radius) :
	ColliderBase(owner, tag),
	radius_(radius)
{
	type_ = ColliderType::TYPE::CIRCLE;
}

ColliderCircle::~ColliderCircle()
{
}

std::shared_ptr<ColliderBase> ColliderCircle::Clone() const
{
	return std::make_shared<ColliderCircle>(*this);
}