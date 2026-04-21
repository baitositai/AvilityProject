#include "UtilityCommon.h"
#include "UtilityCollision.h"

bool UtilityCollision::IsHitArrayToCircle(const std::vector<std::vector<int>>& arrayOfArrays, const std::vector<int>& hitIds, const Vector2& chipSize, ColliderArray::Result& result, const Vector2& circlePos, const float radius)
{ 
    return false;
}

bool UtilityCollision::IsHitArrayToBox(const std::vector<std::vector<int>>& arrayOfArrays, const std::vector<int>& hitIds, const Vector2& chipSize, std::vector<ColliderArray::Result>& results, const Vector2& boxTopPos, const Vector2& boxBottomPos)
{
    // ’ZŒa‚Ì’¸“_‚ğ‚ğƒ}ƒbƒv”Ô†‚É•ÏŠ·
    int startX = boxTopPos.x / chipSize.x - 1;
    int endX = boxBottomPos.x / chipSize.x + 1;
    int startY = boxTopPos.y / chipSize.y - 1;
    int endY = boxBottomPos.y / chipSize.y + 1;

    // Å‘åEÅ¬‚ğİ’è
    if (startX < 0) { startX = 0; }
    if (endX >= (int)arrayOfArrays[0].size()) { endX = (int)arrayOfArrays[0].size() - 1; }
    if (startY < 0) { startY = 0; }
    if (endY >= (int)arrayOfArrays.size()) { endY = (int)arrayOfArrays.size() - 1; }

    bool isHit = false;
    results.clear();

    for (int ty = startY; ty <= endY; ty++)
    {
        for (int tx = startX; tx <= endX; tx++)
        {
            ColliderArray::Result result;
            result.indexes = Vector2(tx, ty);
            result.type = arrayOfArrays[ty][tx];
            result.isHit = UtilityCommon::FindIndex(hitIds, result.type);
            results.push_back(result);
            if (result.isHit) { isHit = true; }
        }
    }

    return isHit;
}

bool UtilityCollision::IsHitCircleToCircle(const Vector2& circlePos1, const float radius1, const Vector2& circlePos2, const float radius2)
{
    // ’†S“_ŠÔ‚ÌXEY‹——£‚ğŒvZ
    float dx = circlePos1.x - circlePos2.x;  // X•ûŒü‚Ì·
    float dy = circlePos1.y - circlePos2.y;  // Y•ûŒü‚Ì·

    // ’†SŠÔ‹——£‚Ì2æ
    float distanceSq = dx * dx + dy * dy;

    // ”¼Œa‚Ì˜a‚Ì2æ
    float radiusSum = radius1 + radius2;
    float radiusSumSq = radiusSum * radiusSum;

    // ”¼Œa‚Ì˜a‚Ì2æ‚æ‚è‹——£‚Ì2æ‚Ì‚Ù‚¤‚ª¬‚³‚¢ê‡Õ“Ë‚µ‚Ä‚¢‚é
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