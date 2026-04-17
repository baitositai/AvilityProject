#include "../Object/ActorBase.h"
#include "ColliderCircle.h"

ColliderCircle::ColliderCircle(ActorBase& owner, const CollisionTags::TAG tag, const float radius) :
	ColliderBase(owner, tag),
	radius_(radius)
{
}

ColliderCircle::~ColliderCircle()
{
}
