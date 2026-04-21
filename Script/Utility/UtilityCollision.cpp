#include "UtilityCommon.h"
#include "UtilityCollision.h"

bool UtilityCollision::IsHitArrayToCircle(const std::vector<std::vector<int>>& arrayOfArrays, const std::vector<int>& hitIds, const Vector2& chipSize, ColliderArray::Result& result, const Vector2& circlePos, const float radius)
{ 
    return false;
}

bool UtilityCollision::IsHitArrayToBox(const std::vector<std::vector<int>>& arrayOfArrays, const std::vector<int>& hitIds, const Vector2& chipSize, ColliderArray::Result& result, const Vector2& boxTopPos, const Vector2& boxBottomPos)
{
    // 配列のサイズを確定
    const int ROWS = static_cast<int>(arrayOfArrays.size());
    if (ROWS == 0) return false;    // 中身がない場合終了
    const int COLS = static_cast<int>(arrayOfArrays[0].size());

    // 最大最小値を決定
    int startX = (std::max)(0, static_cast<int>(boxTopPos.x / chipSize.x));
    int endX = (std::min)(COLS - 1, static_cast<int>(boxBottomPos.x / chipSize.x));
    int startY = (std::max)(0, static_cast<int>(boxTopPos.y / chipSize.y));
    int endY = (std::min)(ROWS - 1, static_cast<int>(boxBottomPos.y / chipSize.y));

    // 範囲チェック
    if (startX > endX || startY > endY) return false;

    // 前回の判定結果を削除
    result.indexes.clear();
    int area = (endX - startX + 1) * (endY - startY + 1);
    result.indexes.reserve(area);

    for (int ty = startY; ty <= endY; ++ty)
    {
        const auto& row = arrayOfArrays[ty];
        for (int tx = startX; tx <= endX; ++tx)
        {
            // 衝突番号を探索する
            if (UtilityCommon::FindIndex(hitIds, row[tx]))
            {
                // インデックスを格納
                result.indexes.emplace_back(static_cast<float>(tx), static_cast<float>(ty));
            }
        }
    }

    return !result.indexes.empty();
}

bool UtilityCollision::IsHitCircleToCircle(const Vector2& circlePos1, const float radius1, const Vector2& circlePos2, const float radius2)
{
    // 中心点間のX・Y距離を計算
    float dx = circlePos1.x - circlePos2.x;  // X方向の差
    float dy = circlePos1.y - circlePos2.y;  // Y方向の差

    // 中心間距離の2乗
    float distanceSq = dx * dx + dy * dy;

    // 半径の和の2乗
    float radiusSum = radius1 + radius2;
    float radiusSumSq = radiusSum * radiusSum;

    // 半径の和の2乗より距離の2乗のほうが小さい場合衝突している
    return distanceSq <= radiusSumSq;
}

bool UtilityCollision::IsHitCircleToBox(const Vector2& circlePos, const float radius, const Vector2& boxTopPos, const Vector2& boxBotmPos)
{
	return false;
}

bool UtilityCollision::IsHitCircleToLine(const Vector2& circlePos, const float radius, const Vector2& lineTopPos, const Vector2& lineEndPos)
{
	return false;
}

bool UtilityCollision::IsHitBoxToBox(const Vector2& boxTopPos1, const Vector2& boxBotmPos1, const Vector2& boxTopPos2, const Vector2& boxBotmPos2)
{
	return false;
}

bool UtilityCollision::IsHitBoxToLine(const Vector2& boxTopPos, const Vector2& boxBotmPos, const Vector2& lineTopPos, const Vector2& lineEndPos)
{
	return false;
}