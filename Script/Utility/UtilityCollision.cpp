#include "UtilityCommon.h"
#include "UtilityCollision.h"

bool UtilityCollision::IsHitArrayToCircle(const std::vector<std::vector<int>>& arrayOfArrays, const std::vector<int>& hitIds, const Vector2& chipSize, ColliderArray::Result& result, const Vector2& circlePos, const float radius)
{ 
    return false;
}

bool UtilityCollision::IsHitArrayToBox(const std::vector<std::vector<int>>& arrayOfArrays, const std::vector<int>& hitIds, const Vector2& chipSize, ColliderArray::Result& result, const Vector2& boxTopPos, const Vector2& boxBottomPos)
{
    // 短径の頂点ををマップ番号に変換
    int startX = boxTopPos.x / chipSize.x;
    int endX = boxBottomPos.x / chipSize.x;
    int startY = boxTopPos.y / chipSize.y;
    int endY = boxBottomPos.y / chipSize.y;

    for (int ty = startY; ty <= endY; ty++)
    {
        for (int tx = startX; tx <= endX; tx++)
        {
            // 範囲外チェック
            if (ty < 0 || ty >= (int)arrayOfArrays.size() || tx < 0 || tx >= (int)arrayOfArrays[0].size())
            {
                continue;
            }

            if (UtilityCommon::FindIndex(hitIds, arrayOfArrays[ty][tx]))
            {
                // 当たったタイルのインデックスを保存して終了
                result.hitIndex.x = tx;
                result.hitIndex.y = ty;
                return true;
            }
        }
    }

    return  false;
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