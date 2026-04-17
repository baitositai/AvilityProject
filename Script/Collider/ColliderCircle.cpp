#include "ColliderCircle.h"

ColliderCircle::ColliderCircle(ActorBase& owner, const CollisionTags tag, const float radius) :
	ColliderBase(owner, tag),
	radius_(radius)
{
}

ColliderCircle::~ColliderCircle()
{
}
