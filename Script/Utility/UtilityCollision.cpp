#include "UtilityCollision.h"

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
