#include <DxLib.h>
#include "../Utility/UtilityCommon.h"
#include "ColliderArray.h"

ColliderArray::ColliderArray(ActorBase& owner, const CollisionTags::TAG tag, Vector2F& followPos, const std::vector<std::vector<int>>& arrayOfArrays, const std::vector<int>& passIndexs, const Vector2& chipSize) :
	ColliderBase(owner, tag, followPos),
	arrayOfArrays_(arrayOfArrays),
	passIndexes_(passIndexs),
	chipSize_(chipSize)
{
	type_ = ColliderType::TYPE::ARRAY;
	result_ = {};
}

ColliderArray::~ColliderArray()
{
}

void ColliderArray::ResetResult()
{
	result_ = {};
}

void ColliderArray::DebugDraw()
{
}

std::shared_ptr<ColliderBase> ColliderArray::Clone() const
{
	return std::make_shared<ColliderArray>(*this);
}

ColliderArray::Result ColliderArray::CheckHitMapChip(const Vector2& worldPos, bool isXAxis, float stepMove) const
{
	Result result{};

	// マップ座標に変換
	int mapX = static_cast<int>(worldPos.x / chipSize_.x);
	int mapY = static_cast<int>(worldPos.y / chipSize_.y);

	// インデックスが配列の範囲内か確認
	if (mapY < 0 || mapY >= static_cast<int>(arrayOfArrays_.size()) ||
		mapX < 0 || mapX >= static_cast<int>(arrayOfArrays_[mapY].size()))
	{
		return result;
	}

	int chipIndex = arrayOfArrays_[mapY][mapX];

	// 空白チップなら当たり判定なし
	if (chipIndex <= -1)
	{
		return result;
	}

	// すり抜け床かどうかチェック
	bool isPassFloor = false;
	for (int passIndex : passIndexes_)
	{
		if (chipIndex == passIndex)
		{
			isPassFloor = true;
			break;
		}
	}

	if (isPassFloor)
	{
		if (isXAxis)
		{
			return result;
		}

		if (stepMove <= 0.0f)
		{
			return result;
		}

		float previousBottomY = worldPos.y - stepMove;
		float floorTopY = static_cast<float>(mapY * chipSize_.y);

		if (previousBottomY > floorTopY + 1.0f)
		{
			return result;
		}
	}

	// 衝突フラグを立てる
	result.hit = true;
	result.chipSize = chipSize_;
	result.hitChipIndex = { mapX, mapY };

	return result;
}