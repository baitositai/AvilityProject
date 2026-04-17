#include "../Object/ActorBase.h"
#include "ColliderLine.h"
#include "ColliderBox.h"

ColliderLine::ColliderLine(ActorBase& owner, const CollisionTags::TAG tag, const Vector2& topPos, const Vector2& endPos) :
	ColliderBase(owner, tag),
	topPos_(topPos),
	endPos_(endPos)
{
}

ColliderLine::~ColliderLine()
{
}

const Vector2& ColliderLine::GetLocalTopPos() const
{
	Vector2F posF = owner_.GetParameter()->pos;
	Vector2 pos = posF.ToVector2();
	pos = Vector2::AddVector2(pos, topPos_);
	return pos;
}

const Vector2& ColliderLine::GetLocalEndPos() const
{
	Vector2F posF = owner_.GetParameter()->pos;
	Vector2 pos = posF.ToVector2();
	pos = Vector2::AddVector2(pos, endPos_);
	return pos;
}
