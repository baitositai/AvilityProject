#include "ColliderBox.h"

ColliderBox::ColliderBox(ActorBase& owner, const CollisionTags::TAG tag, const Vector2& topPos, const Vector2& endPos) :
	ColliderBase(owner, tag),
	topPos_(topPos),
	endPos_(endPos)
{
}

ColliderBox::~ColliderBox()
{
}
