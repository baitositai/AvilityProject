#include "ColliderBase.h"

ColliderBase::ColliderBase(const ActorBase& owner, const CollisionTags::TAG tag) :
	owner_(owner),
	TAG(tag)
{
}

ColliderBase::~ColliderBase()
{
}
