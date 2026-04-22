#include "Utility2D.h"
#include <cmath>

double Utility2D::Magnitude(const Vector2& v)
{
    return sqrt((v.x * v.x) + (v.y * v.y));
}

int Utility2D::SqrMagnitude(const Vector2& v)
{
    return v.x * v.x + v.y * v.y;
}

double Utility2D::Distance(const Vector2& v1, const Vector2& v2)
{
    return sqrt(pow(v2.x - v1.x, 2) + pow(v2.y - v1.y, 2));
}

float Utility2D::Dot(const Vector2F& v1, const Vector2F& v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}



Vector2 Utility2D::WorldToMapPos(const Vector2& worldPos, const Vector2& mapSize)
{
    Vector2 mapPos = worldPos;
    mapPos.x = static_cast<int>(worldPos.x / mapSize.x);
    mapPos.y = static_cast<int>(worldPos.y / mapSize.y);
    return mapPos;
}

Vector2 Utility2D::MapToWorldPos(const Vector2& mapPos, const Vector2& mapSize)
{
    Vector2 worldPos = mapPos;
    worldPos.x = static_cast<int>(mapPos.x * mapSize.x);
    worldPos.y = static_cast<int>(mapPos.y * mapSize.y);
    return worldPos;
}

bool Utility2D::IsHitCircles(const Vector2& circlePos1, const float radius1, const Vector2& circlePos2, const float radius2)
{
    // ’†S“_ŠÔ‚ÌXEY‹——£‚ğŒvZ
    float dx = circlePos1.x - circlePos2.x;  // X•ûŒü‚Ì·
    float dy = circlePos1.y - circlePos2.y;  // Y•ûŒü‚Ì·

    // ’†SŠÔ‹——£‚Ì2æ
    float distanceSq = dx * dx + dy * dy;

    // ”¼Œa‚Ì˜a‚Ì2æ
    float radiusSum = radius1 + radius2;
    float radiusSumSq = radiusSum * radiusSum;

    // ‹——£‚Ì2æ <= ”¼Œa‚Ì˜a‚Ì2æ ¨ Õ“Ë
    return distanceSq <= radiusSumSq;
}
