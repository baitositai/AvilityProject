#include <DxLib.h>
#include "../Manager/Common/SceneManager.h"
#include "../Manager/Common/Camera.h"
#include "../Utility/UtilityCommon.h"
#include "../Utility/Utility2D.h"
#include "../Object/ActorBase.h"
#include "ColliderBox.h"

ColliderBox::ColliderBox(ActorBase& owner, const CollisionTags::TAG tag, Vector2F& followPos, Vector2& boxSize, float& radAngle) :
	ColliderBase(owner, tag, followPos),
	boxSize_(boxSize),
	radAngle_(radAngle)
{	
	type_ = ColliderType::TYPE::BOX;
}

ColliderBox::~ColliderBox()
{
}

const Vector2& ColliderBox::GetBoxHalfSize() const
{
	return Vector2(boxSize_.x / 2, boxSize_.y / 2);
}

Vector2F ColliderBox::GetAABBMin() const
{
	auto vertices = GetRotatedVertices();

	float minX = (std::min)({
		vertices[0].x,
		vertices[1].x,
		vertices[2].x,
		vertices[3].x
		});

	float minY = (std::min)({
		vertices[0].y,
		vertices[1].y,
		vertices[2].y,
		vertices[3].y
		});

	return Vector2F(minX, minY);
}

Vector2F ColliderBox::GetAABBMax() const
{
	auto vertices = GetRotatedVertices();

	float maxX = (std::max)({
		vertices[0].x,
		vertices[1].x,
		vertices[2].x,
		vertices[3].x
		});

	float maxY = (std::max)({
		vertices[0].y,
		vertices[1].y,
		vertices[2].y,
		vertices[3].y
		});

	return Vector2F(maxX, maxY);
}

std::vector<Vector2F> ColliderBox::GetRotatedVertices() const
{
	std::vector<Vector2F> vertices(4);

	// 現在の回転角に基づいた軸ベクトル（単位ベクトル）
	Vector2F axisX = GetAxisX();
	Vector2F axisY = GetAxisY();

	float hW = static_cast<float>(boxSize_.x / 2);
	float hH = static_cast<float>(boxSize_.y / 2);

	// 各頂点（0:左上, 1:右上, 2:右下, 3:左下）を計算
	// 計算式: 中心点 + (X軸方向 * ±横幅) + (Y軸方向 * ±縦幅)

	// 0: 左上 (Top-Left)
	vertices[0].x = followPos_.x + (axisX.x * -hW) + (axisY.x * -hH);
	vertices[0].y = followPos_.y + (axisX.y * -hW) + (axisY.y * -hH);

	// 1: 右上 (Top-Right)
	vertices[1].x = followPos_.x + (axisX.x * hW) + (axisY.x * -hH);
	vertices[1].y = followPos_.y + (axisX.y * hW) + (axisY.y * -hH);

	// 2: 右下 (Bottom-Right)
	vertices[2].x = followPos_.x + (axisX.x * hW) + (axisY.x * hH);
	vertices[2].y = followPos_.y + (axisX.y * hW) + (axisY.y * hH);

	// 3: 左下 (Bottom-Left)
	vertices[3].x = followPos_.x + (axisX.x * -hW) + (axisY.x * hH);
	vertices[3].y = followPos_.y + (axisX.y * -hW) + (axisY.y * hH);

	return vertices;
}

void ColliderBox::DebugDraw()
{
	if (!isActive_ || !owner_.IsActive()) return;

	auto v = GetRotatedVertices();
	Vector2F cameraPos = mainCamera.GetPos();
	int offsetX = static_cast<int>(cameraPos.x);
	int offsetY = static_cast<int>(cameraPos.y);

	// DrawBoxは回転に対応していないため、DrawLineで4辺を描画する
	unsigned int color = UtilityCommon::RED;
	DrawLine(v[0].x + offsetX, v[0].y + offsetY, v[1].x + offsetX, v[1].y + offsetY, color);
	DrawLine(v[1].x + offsetX, v[1].y + offsetY, v[2].x + offsetX, v[2].y + offsetY, color);
	DrawLine(v[2].x + offsetX, v[2].y + offsetY, v[3].x + offsetX, v[3].y + offsetY, color);
	DrawLine(v[3].x + offsetX, v[3].y + offsetY, v[0].x + offsetX, v[0].y + offsetY, color);

	// 各頂点を円で描画（回転後の位置が正しいか確認用）
	constexpr float RADIUS = 5.0f;
	DrawCircle(v[0].x + offsetX, v[0].y + offsetY, RADIUS, UtilityCommon::PURPLE, true); // 左上相当
	DrawCircle(v[2].x + offsetX, v[2].y + offsetY, RADIUS, UtilityCommon::PINK, true);   // 右下相当
}

Vector2F ColliderBox::GetAxisX(void) const
{
	return Vector2F(std::cos(radAngle_), std::sin(radAngle_));
}

Vector2F ColliderBox::GetAxisY(void) const
{
	return Vector2F(-std::sin(radAngle_), std::cos(radAngle_));
}

bool ColliderBox::OverlapOnAxis(const std::weak_ptr<ColliderBox>& opponent, const Vector2F& axis)
{
	Vector2 boxHalfSize = GetBoxHalfSize();


	Vector2F cameraPos = mainCamera.GetPos();
	Vector2 pos = Vector2::AddVector2(followPos_.ToVector2(), cameraPos.ToVector2());

	//自分の軸
	Vector2F axA = GetAxisX();
	Vector2F ayA = GetAxisY();

	//相手の軸
	Vector2F axB = opponent.lock()->GetAxisX();
	Vector2F ayB = opponent.lock()->GetAxisY();
	
	//中心の投影
	float aCenter = Utility2D::Dot(followPos_, axis);
	float bCenter = Utility2D::Dot(opponent.lock()->GetOwner().GetParameter().pos_, axis);

	//投影の広がり
	float aRadius = static_cast<float>(boxHalfSize.x) * std::fabs(Utility2D::Dot(axA, axis)) +
					static_cast<float>(boxHalfSize.y) * std::fabs(Utility2D::Dot(ayA, axis));
	float bRadius = static_cast<float>(opponent.lock()->GetBoxHalfSize().x) * std::fabs(Utility2D::Dot(axB, axis))+
					static_cast<float>(opponent.lock()->GetBoxHalfSize().y) * std::fabs(Utility2D::Dot(ayB, axis));

	return std::fabs(aCenter - bCenter) <= (aRadius + bRadius);
}

std::shared_ptr<ColliderBase> ColliderBox::Clone() const
{
	return std::make_shared<ColliderBox>(*this);
}