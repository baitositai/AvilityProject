#include "../Object/ActorBase.h"
#include "ColliderBox.h"

ColliderBox::ColliderBox(ActorBase& owner, const CollisionTags::TAG tag, const Vector2& topPos, const Vector2& bottomPos) :
	ColliderBase(owner, tag),
	topPos_(topPos),
	bottomPos_(bottomPos)
{
}

ColliderBox::~ColliderBox()
{
}

const Vector2& ColliderBox::GetLocalTopPos() const
{
	Vector2F posF = owner_.GetParameter()->pos;
	Vector2 pos = posF.ToVector2();
	pos = Vector2::AddVector2(pos, topPos_);
	return pos;
}

const Vector2& ColliderBox::GetLocalBottomPos() const
{
	Vector2F posF = owner_.GetParameter()->pos;
	Vector2 pos = posF.ToVector2();
	pos = Vector2::AddVector2(pos, bottomPos_);
	return pos;
}