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
    return false;
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
    // lŠpŒ`‚Ì”ÍˆÍ“à‚Å‰~‚Ì’†S‚ÉÅ‚à‹ß‚¢À•W‚ğ“Á’è‚·‚é
    float closestX = (std::max)(boxTopPos.x, (std::min)(circlePos.x, boxBotmPos.x));
    float closestY = (std::max)(boxTopPos.y, (std::min)(circlePos.y, boxBotmPos.y));

    // Å’Z’n“_‚Æ‰~‚Ì’†S‚Æ‚Ì‹——£‚Ì2æ‚ğŒvZ‚·‚é
    float diffX = circlePos.x - closestX;
    float diffY = circlePos.y - closestY;
    float distanceSq = (diffX * diffX) + (diffY * diffY);

    // ‹——£‚Ì2æ‚ª”¼Œa‚Ì2æˆÈ‰º‚È‚çÕ“Ë‚µ‚Ä‚¢‚é
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


