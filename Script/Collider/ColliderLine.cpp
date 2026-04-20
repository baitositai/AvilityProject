#include "../Object/ActorBase.h"
#include "ColliderLine.h"

ColliderLine::ColliderLine(ActorBase& owner, const CollisionTags::TAG tag, const Vector2& topPos, const Vector2& endPos) :
	ColliderBase(owner, tag),
	topPos_(topPos),
	endPos_(endPos)
{
	type_ = ColliderType::TYPE::LINE;
}

ColliderLine::~ColliderLine()
{
}

std::shared_ptr<ColliderBase> ColliderLine::Clone() const
{
	return std::shared_ptr<ColliderLine>();
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
