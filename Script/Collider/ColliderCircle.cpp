#include <DxLib.h>
#include "../Object/ActorBase.h"
#include "ColliderCircle.h"

ColliderCircle::ColliderCircle(ActorBase& owner, const CollisionTags::TAG tag, Vector2F& followPos, const float radius) :
	ColliderBase(owner, tag, followPos),
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

void ColliderCircle::DebugDraw()
{
	if (!isActive_ || !owner_.IsActive()) return;
	Vector2 pos = followPos_.ToVector2();
	DrawCircle(pos.x, pos.y, radius_,  0xff0000, false , 3);
}
