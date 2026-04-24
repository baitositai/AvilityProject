#include <DxLib.h>
#include "../Utility/UtilityCommon.h"
#include "../Utility/Utility2D.h"
#include "../Object/ActorBase.h"
#include "ColliderBox.h"

ColliderBox::ColliderBox(ActorBase& owner, const CollisionTags::TAG tag, Vector2F& followPos, const Vector2& boxSize, float& radAngle) :
	ColliderBase(owner, tag, followPos),
	boxSize_(boxSize),
	radAngle_(radAngle),
	boxHalfSize_(Vector2(boxSize_.x / 2, boxSize_.y / 2))
{	
	type_ = ColliderType::TYPE::BOX;
}

ColliderBox::~ColliderBox()
{
}

const Vector2& ColliderBox::GetLocalTopPos() const
{
	Vector2 pos = Vector2::AddVector2(followPos_.ToVector2(), Vector2::MultiVector2(boxHalfSize_, Vector2(-1, -1)));
	return pos;
}

const Vector2& ColliderBox::GetLocalBottomPos() const
{
	Vector2 pos = Vector2::AddVector2(followPos_.ToVector2(), boxHalfSize_);
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

	// äeí∏ì_Çâ~Ç≈ï`âÊ
	constexpr float RADIUS = 5.0f;
	DrawCircle(top.x, top.y, RADIUS, UtilityCommon::PURPLE, true);
	DrawCircle(top.x, top.y + boxSize_.y, RADIUS, UtilityCommon::BLACK, true);
	DrawCircle(top.x + boxSize_.x, top.y, RADIUS, UtilityCommon::BLACK, true);

	DrawCircle(bottom.x, bottom.y, RADIUS, UtilityCommon::PINK, true);
	DrawCircle(bottom.x, bottom.y - boxSize_.y, RADIUS, UtilityCommon::BLACK, true);
	DrawCircle(bottom.x - boxSize_.x, bottom.y, RADIUS, UtilityCommon::BLACK, true);
}

const Vector2F& ColliderBox::GetAxisX(void)const
{
	return Vector2F(std::cos(radAngle_), std::sin(radAngle_));
}

const Vector2F& ColliderBox::GetAxisY(void)const
{
	return Vector2F(-std::sin(radAngle_),std::cos(radAngle_));
}

bool ColliderBox::OverlapOnAxis(const std::weak_ptr<ColliderBox>& opponent, const Vector2F& axis)
{
	//é©ï™ÇÃé≤
	Vector2F axA = GetAxisX();
	Vector2F ayA = GetAxisY();

	//ëäéËÇÃé≤
	Vector2F axB = opponent.lock()->GetAxisX();
	Vector2F ayB = opponent.lock()->GetAxisY();
	
	//íÜêSÇÃìäâe
	float aCenter = Utility2D::Dot(followPos_, axis);
	float bCenter = Utility2D::Dot(opponent.lock()->GetOwner().GetParameter()->pos, axis);

	//ìäâeÇÃçLÇ™ÇË
	float aRadius = static_cast<float>(boxHalfSize_.x) * std::fabs(Utility2D::Dot(axA, axis)) +
					static_cast<float>(boxHalfSize_.y) * std::fabs(Utility2D::Dot(ayA, axis));
	float bRadius = static_cast<float>(opponent.lock()->GetBoxHalfSize().x) * std::fabs(Utility2D::Dot(axB, axis))+
					static_cast<float>(opponent.lock()->GetBoxHalfSize().y) * std::fabs(Utility2D::Dot(ayB, axis));


	return std::fabs(aCenter - bCenter) <= (aRadius + bRadius);
}

std::shared_ptr<ColliderBase> ColliderBox::Clone() const
{
	return std::make_shared<ColliderBox>(*this);
}