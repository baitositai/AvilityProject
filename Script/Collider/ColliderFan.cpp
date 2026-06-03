#include <DxLib.h>
#include "../Manager/Common/SceneManager.h"
#include "../Manager/Common/Camera.h"
#include "../Utility/UtilityCommon.h"
#include "../Object/ActorBase.h"
#include "ColliderFan.h"

ColliderFan::ColliderFan(ActorBase& owner, const CollisionTags::TAG tag, Vector2F& followPos, float& radius, float& baseAngle, float& viewAngle) :
	ColliderBase(owner, tag, followPos),
	radius_(radius),
	viewAngle_(viewAngle),
	baseAngle_(baseAngle)
{
    type_ = ColliderType::TYPE::FAN;
}

ColliderFan::~ColliderFan()
{
}

void ColliderFan::DebugDraw()
{
    // カメラ座標取得
    Vector2F cameraPos = mainCamera.GetPos();

    // 中心座標を取得
    Vector2F center = Vector2F::AddVector2F(followPos_, cameraPos);

    // 視野角の半分を計算
    float halfAngleRad = viewAngle_ * 0.5f;

    // 扇形の左端と右端の角度を計算
    float startAngleRad = baseAngle_ - halfAngleRad;
    float endAngleRad = baseAngle_ + halfAngleRad;

    // 左端の境界線の先端座標
    int leftEndX = static_cast<int>(center.x + cosf(startAngleRad) * radius_);
    int leftEndY = static_cast<int>(center.y + sinf(startAngleRad) * radius_);

    // 右端の境界線の先端座標
    int rightEndX = static_cast<int>(center.x + cosf(endAngleRad) * radius_);
    int rightEndY = static_cast<int>(center.y + sinf(endAngleRad) * radius_);

    // 中心からそれぞれの先端へ線を引く
    DrawLine(static_cast<int>(center.x), static_cast<int>(center.y), leftEndX, leftEndY, UtilityCommon::YELLOW);
    DrawLine(static_cast<int>(center.x), static_cast<int>(center.y), rightEndX, rightEndY, UtilityCommon::YELLOW);

    // 円弧を何本の直線で細分化して表現するか
    const int DIVIDE_COUNT = 16;
    float angleStep = (endAngleRad - startAngleRad) / DIVIDE_COUNT;

    Vector2F previousPoint = { static_cast<float>(leftEndX), static_cast<float>(leftEndY) };

    for (int i = 1; i <= DIVIDE_COUNT; ++i)
    {
        float currentAngle = startAngleRad + (angleStep * i);

        Vector2F currentPoint;
        currentPoint.x = center.x + cosf(currentAngle) * radius_;
        currentPoint.y = center.y + sinf(currentAngle) * radius_;

        // 前の点から現在の点へ線を引くことで、綺麗なカーブを作る
        DrawLine(
            static_cast<int>(previousPoint.x), static_cast<int>(previousPoint.y),
            static_cast<int>(currentPoint.x), static_cast<int>(currentPoint.y),
            UtilityCommon::YELLOW
        );

        previousPoint = currentPoint;
    }
}

std::shared_ptr<ColliderBase> ColliderFan::Clone() const
{
    return std::make_shared<ColliderFan>(*this);
}
