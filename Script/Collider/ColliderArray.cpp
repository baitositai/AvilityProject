#include <DxLib.h>
#include "../Utility/UtilityCommon.h"
#include "ColliderArray.h"

ColliderArray::ColliderArray(ActorBase& owner, const CollisionTags::TAG tag, Vector2F& followPos, const std::vector<std::vector<int>>& arrayOfArrays, const Vector2& chipSize) :
	ColliderBase(owner, tag, followPos),
	arrayOfArrays_(arrayOfArrays),
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

ColliderArray::Result ColliderArray::CheckHitMapChip(const Vector2& worldPos) const
{
	Result result{};

	// マップ座標に変換
	int mapX = worldPos.x / chipSize_.x;
	int mapY = worldPos.y / chipSize_.y;

	// インデックスが配列の範囲内か確認
	if (mapY < 0 || mapY >= static_cast<int>(arrayOfArrays_.size()) ||
		mapX < 0 || mapX >= static_cast<int>(arrayOfArrays_[mapY].size()))
	{
		return result;
	}

	// 結果
	result.hit = -1 < arrayOfArrays_[mapY][mapX];

	// 衝突している場合
	if (result.hit)
	{
		// 押し出し用のチップ情報を格納
		result.chipSize = chipSize_;
		result.hitChipIndex = { mapX, mapY };
	}

	// 結果を返す
	return result;
}