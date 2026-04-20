#include <DxLib.h>
#include "../Utility/UtilityCommon.h"
#include "../Object/ActorBase.h"
#include "ColliderBox.h"

ColliderBox::ColliderBox(ActorBase& owner, const CollisionTags::TAG tag, const Vector2& boxSize) :
	ColliderBase(owner, tag),
	boxSize_(boxSize),
	boxHalfSize_(Vector2(boxSize_.x / 2, boxSize_.y / 2))
{
	type_ = ColliderType::TYPE::BOX;
}

ColliderBox::~ColliderBox()
{
}

const Vector2& ColliderBox::GetLocalTopPos() const
{
	Vector2F posF = owner_.GetParameter()->pos;
	Vector2 pos = posF.ToVector2();		
	pos = Vector2::AddVector2(pos, Vector2::MultiVector2(boxHalfSize_, Vector2(-1, -1)));
	return pos;
}

const Vector2& ColliderBox::GetLocalBottomPos() const
{
	Vector2F posF = owner_.GetParameter()->pos;
	Vector2 pos = posF.ToVector2();
	pos = Vector2::AddVector2(pos, boxHalfSize_);
	return pos;
}

void ColliderBox::DebugDraw()
{
	Vector2 top = GetLocalTopPos();
	Vector2 bottom = GetLocalBottomPos();

	DrawBox(
		top.x,
		top.y,
		bottom.x,
		bottom.y,
		UtilityCommon::RED,
		false
	);

	// Še’¸“_‚ð‰~‚Å•`‰æ
	constexpr float RADIUS = 5.0f;
	DrawCircle(top.x, top.y, RADIUS, UtilityCommon::PURPLE, true);
	DrawCircle(top.x, top.y + boxSize_.y, RADIUS, UtilityCommon::BLACK, true);
	DrawCircle(top.x + boxSize_.x, top.y, RADIUS, UtilityCommon::BLACK, true);

	DrawCircle(bottom.x, bottom.y, RADIUS, UtilityCommon::PINK, true);
	DrawCircle(bottom.x, bottom.y - boxSize_.y, RADIUS, UtilityCommon::BLACK, true);
	DrawCircle(bottom.x - boxSize_.x, bottom.y, RADIUS, UtilityCommon::BLACK, true);
}

std::shared_ptr<ColliderBase> ColliderBox::Clone() const
{
	return std::make_shared<ColliderBox>(*this);
}