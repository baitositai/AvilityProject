#include "../../Object/ActorBase.h"
#include "UtilityCommon.h"
#include "UtilityCollision.h"

bool UtilityCollision::IsHitArrayToCircle(const std::vector<std::vector<int>>& arrayOfArrays, const std::vector<int>& hitIds, const Vector2& chipSize, ColliderArray::Result& result, const Vector2& circlePos, const float radius)
{ 
    return false;
}

bool UtilityCollision::IsHitArrayToBox(const std::vector<std::vector<int>>& arrayOfArrays,
    const std::vector<int>& hitIds,
    const Vector2& chipSize,
    ColliderArray::Result& result,
    const Vector2F& boxTopPos,
    const Vector2F& boxBottomPos,
    const Vector2F& moveAmount,
    ParameterActor::DIR gravityDir)
{
    // 初期化（念のため最初に結果をクリアしておく）
    result.hit = false;
    result.chipSize = chipSize;

    if (arrayOfArrays.empty() || arrayOfArrays[0].empty()) return false;
    if (chipSize.x <= 0 || chipSize.y <= 0) return false;

    int mapWidthChips = static_cast<int>(arrayOfArrays[0].size());
    int mapHeightChips = static_cast<int>(arrayOfArrays.size());

    int startX = static_cast<int>(boxTopPos.x) / chipSize.x;
    int endX = static_cast<int>(boxBottomPos.x) / chipSize.x;
    int startY = static_cast<int>(boxTopPos.y) / chipSize.y;
    int endY = static_cast<int>(boxBottomPos.y) / chipSize.y;

    startX = (std::max)(0, (std::min)(startX, mapWidthChips - 1));
    endX = (std::max)(0, (std::min)(endX, mapWidthChips - 1));
    startY = (std::max)(0, (std::min)(startY, mapHeightChips - 1));
    endY = (std::max)(0, (std::min)(endY, mapHeightChips - 1));

    bool isHitAny = false;

    // めり込みが最も深いタイルを特定するために、中心に近いタイルを優先するなどの処理用
    // 今回は最初に見つかった「衝突タイル」のインデックスを記録します
    for (int y = startY; y <= endY; ++y)
    {
        for (int x = startX; x <= endX; ++x)
        {
            int chipId = arrayOfArrays[y][x];

            auto it = std::find(hitIds.begin(), hitIds.end(), chipId);
            if (it != hitIds.end())
            {
                // 衝突検知！
                isHitAny = true;

                // 【ここが重要！】OnHitStageが必要としているデータをresultに格納
                result.hit = true;
                result.hitChipIndex = Vector2(x, y);

                // 1つ見つかれば押し戻し処理の基準にできるため、ここでループを抜けてもOKです
                return true;
            }
        }
    }

    return isHitAny;
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
    // 四角形の範囲内で円の中心に最も近い座標を特定する
    float closestX = (std::max)(boxTopPos.x, (std::min)(circlePos.x, boxBotmPos.x));
    float closestY = (std::max)(boxTopPos.y, (std::min)(circlePos.y, boxBotmPos.y));

    // 最短地点と円の中心との距離の2乗を計算する
    float diffX = circlePos.x - closestX;
    float diffY = circlePos.y - closestY;
    float distanceSq = (diffX * diffX) + (diffY * diffY);

    // 距離の2乗が半径の2乗以下なら衝突している
    return distanceSq <= (radius * radius);
}

bool UtilityCollision::IsHitCircleToLine(const Vector2& circlePos, const float radius, const Vector2& lineTopPos, const Vector2& lineEndPos)
{
	return false;
}

bool UtilityCollision::IsHitBoxToBox(const Vector2& boxTopPos1, const Vector2& boxBotmPos1, const float degAngle1,
    const Vector2& boxTopPos2, const Vector2& boxBotmPos2,const float degAngle2)
{

	return false;
}

bool UtilityCollision::IsHitBoxToLine(const Vector2& boxTopPos, const Vector2& boxBotmPos, const Vector2& lineTopPos, const Vector2& lineEndPos)
{
	return false;
}


