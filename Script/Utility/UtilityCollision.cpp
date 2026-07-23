#include <DxLib.h>
#include <algorithm>
#include "../../Object/ActorBase.h"
#include "UtilityCommon.h"
#include "UtilityCollision.h"
#include "Utility2D.h"

bool UtilityCollision::IsHitArrayToCircle(
	const std::vector<std::vector<int>>& arrayOfArrays,
	const std::vector<int>& hitIds,
	const Vector2& chipSize,
	ColliderArray::Result& result,
	const Vector2& circlePos,
	const float radius,
	Vector2& hitPos)
{
	return false;
}

bool UtilityCollision::IsHitArrayToBox(
	const std::vector<std::vector<int>>& arrayOfArrays,
	const std::vector<int>& hitIds,
	const Vector2& chipSize,
	ColliderArray::Result& result,
	const Vector2F& boxTopPos,
	const Vector2F& boxBottomPos,
	const Vector2F& moveAmount,
	ParameterActor::DIR gravityDir,
	Vector2& hitPos)
{
	return false;
}

bool UtilityCollision::IsHitCircleToCircle(
	const Vector2& circlePos1,
	const float radius1,
	const Vector2& circlePos2,
	const float radius2,
	Vector2& hitPos)
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
	if (distanceSq <= radiusSumSq)
	{
		// 距離が0の場合は円1の座標をそのまま衝突位置とする
		if (distanceSq == 0.0f)
		{
			hitPos = circlePos1;
		}
		else
		{
			// お互いの半径の比率を利用して衝突位置を計算する
			float distance = sqrtf(distanceSq);
			float ratio = radius1 / (radius1 + radius2);
			hitPos.x = circlePos1.x - (dx * ratio);
			hitPos.y = circlePos1.y - (dy * ratio);
		}
		return true;
	}

	return false;
}

bool UtilityCollision::IsHitCircleToBox(
	const Vector2& circlePos,
	const float radius,
	const Vector2& boxTopPos,
	const Vector2& boxBotmPos,
	Vector2& hitPos)
{
	// 座標の上下左右関係が逆転していても安全なように最小値・最大値を求める
	float minX = std::min<float>(boxTopPos.x, boxBotmPos.x);
	float maxX = std::max<float>(boxTopPos.x, boxBotmPos.x);
	float minY = std::min<float>(boxTopPos.y, boxBotmPos.y);
	float maxY = std::max<float>(boxTopPos.y, boxBotmPos.y);

	// clampの型を明示的に指定する
	float closestX = std::clamp<float>(circlePos.x, minX, maxX);
	float closestY = std::clamp<float>(circlePos.y, minY, maxY);

    // 最短地点と円の中心との距離の2乗を計算する
    float diffX = circlePos.x - closestX;
    float diffY = circlePos.y - closestY;
    float distanceSq = (diffX * diffX) + (diffY * diffY);

    // わずかな浮動小数点誤差を許容するための許容値
    const float EPSILON = 0.00001f;

    // 距離の2乗が半径の2乗以下なら衝突している
    if (distanceSq <= (radius * radius) + EPSILON)
    {
        // ボックス上の最も近い点を衝突位置とする
        hitPos.x = closestX;
        hitPos.y = closestY;
        return true;
    }

    return false;
}

bool UtilityCollision::IsHitCircleToLine(
	const Vector2& circlePos,
	const float radius,
	const Vector2& lineTopPos,
	const Vector2& lineEndPos,
	Vector2& hitPos)
{
	return false;
}

bool UtilityCollision::IsHitBoxToBox(
	const Vector2& boxTopPos1,
	const Vector2& boxBotmPos1,
	const float degAngle1,
	const Vector2& boxTopPos2,
	const Vector2& boxBotmPos2,
	const float degAngle2,
	Vector2& hitPos)
{
	float radAngle1 = degAngle1 * DX_PI_F / 180.0f;
	float radAngle2 = degAngle2 * DX_PI_F / 180.0f;

	Vector2 centerPos1 = (boxTopPos1 + boxBotmPos1) * 0.5f;
	Vector2 centerPos2 = (boxTopPos2 + boxBotmPos2) * 0.5f;

	Vector2 halfSize1 = (boxBotmPos1 - boxTopPos1) * 0.5f;
	Vector2 halfSize2 = (boxBotmPos2 - boxTopPos2) * 0.5f;

	Vector2 axes1[2];
	axes1[0] = Vector2(cosf(radAngle1), sinf(radAngle1));
	axes1[1] = Vector2(-sinf(radAngle1), cosf(radAngle1));

	Vector2 axes2[2];
	axes2[0] = Vector2(cosf(radAngle2), sinf(radAngle2));
	axes2[1] = Vector2(-sinf(radAngle2), cosf(radAngle2));

	Vector2 axes[4] =
	{
		axes1[0],
		axes1[1],
		axes2[0],
		axes2[1]
	};

	Vector2 toCenter = centerPos2 - centerPos1;

	for (int i = 0; i < 4; ++i)
	{
		Vector2 currentAxis = axes[i];

		float centerProjection = fabsf(Utility2D::Dot(toCenter, currentAxis));

		float extents1 =
			fabsf(Utility2D::Dot(axes1[0], currentAxis)) * halfSize1.x +
			fabsf(Utility2D::Dot(axes1[1], currentAxis)) * halfSize1.y;

		float extents2 =
			fabsf(Utility2D::Dot(axes2[0], currentAxis)) * halfSize2.x +
			fabsf(Utility2D::Dot(axes2[1], currentAxis)) * halfSize2.y;

		if (centerProjection > extents1 + extents2)
		{
			return false;
		}
	}

	hitPos = (centerPos1 + centerPos2) * 0.5f;

	return true;
}

bool UtilityCollision::IsHitBoxToLine(
	const Vector2& boxTopPos,
	const Vector2& boxBotmPos,
	const Vector2& lineTopPos,
	const Vector2& lineEndPos,
	Vector2& hitPos)
{
	return false;
}

bool UtilityCollision::IsHitBoxToFan(
	const Vector2& boxTopPos,
	const Vector2& boxBotmPos,
	const Vector2& fanPos,
	float radius,
	float baseAngleRad,
	float viewAngleRad,
	Vector2& hitPos)
{
	// 矩形の4頂点を配列に格納する
	Vector2 boxVertices[4];
	boxVertices[0] = { boxTopPos.x, boxTopPos.y }; // 左上
	boxVertices[1] = { boxBotmPos.x, boxTopPos.y }; // 右上
	boxVertices[2] = { boxTopPos.x, boxBotmPos.y }; // 左下
	boxVertices[3] = { boxBotmPos.x, boxBotmPos.y }; // 右下

	// 視野角をラジアンの半分に変換
	float halfAngleRad = viewAngleRad * 0.5f;

	// 矩形の各頂点に対して判定を行う
	for (int i = 0; i < 4; ++i)
	{
		// 扇形の中心から頂点へのベクトルを計算する
		float diffX = boxVertices[i].x - fanPos.x;
		float diffY = boxVertices[i].y - fanPos.y;

		// 距離の判定（円形判定と同じ）
		float distanceSq = (diffX * diffX) + (diffY * diffY);
		if (distanceSq > (radius * radius))
		{
			continue; // この頂点は射程外なので次の頂点へ
		}

		// 角度の判定
		// atan2fで頂点への角度を求め、敵の正面角度との差分を計算する
		float angleToTarget = atan2f(diffY, diffX);
		float angleDiff = angleToTarget - baseAngleRad;

		// 角度差を -PI から PI の範囲に正規化する
		while (angleDiff > DX_PI_F) angleDiff -= DX_PI_F * 2.0f;
		while (angleDiff < -DX_PI_F) angleDiff += DX_PI_F * 2.0f;

		// 角度差の絶対値が視野角の半分以内なら視界内とみなす
		if (fabsf(angleDiff) <= halfAngleRad)
		{
			// ヒットした矩形の頂点を衝突位置とする
			hitPos = boxVertices[i];
			return true; // 1点でも入っていればヒット
		}
	}

	return false;
}

bool UtilityCollision::IsHitCircleToFan(
	const Vector2& circlePos,
	float circleRadius,
	const Vector2& fanPos,
	float radius,
	float baseAngleRad,
	float viewAngleRad,
	Vector2& hitPos)
{
	// 扇形の中心から円の中心へのベクトルを計算する
	float diffX = circlePos.x - fanPos.x;
	float diffY = circlePos.y - fanPos.y;

	// 距離の判定
	// 円の半径分だけ、あらかじめ判定の射程（半径）を広げて計算する
	float totalRadius = radius + circleRadius;
	float distanceSq = (diffX * diffX) + (diffY * diffY);

	if (distanceSq > (totalRadius * totalRadius))
	{
		return false; // 射程外
	}

	// 角度の判定
	// 視野角をラジアンの半分に変換
	float halfAngleRad = viewAngleRad * 0.5f;

	// atan2fで円の中心への角度を求め、正面角度との差分を計算
	float angleToTarget = atan2f(diffY, diffX);
	float angleDiff = angleToTarget - baseAngleRad;

	// 角度差を -PI から PI の範囲に正規化
	while (angleDiff > DX_PI_F) angleDiff -= DX_PI_F * 2.0f;
	while (angleDiff < -DX_PI_F) angleDiff += DX_PI_F * 2.0f;

	// 角度差の絶対値が視野角の半分以内の場合
	if (fabsf(angleDiff) <= halfAngleRad)
	{
		// 簡易的に円の中心方向へ向かう扇形の外周境界を衝突位置とする
		float distance = sqrtf(distanceSq);
		if (distance > 0.0f)
		{
			hitPos.x = fanPos.x + (diffX / distance) * radius;
			hitPos.y = fanPos.y + (diffY / distance) * radius;
		}
		else
		{
			hitPos = fanPos;
		}
		return true;
	}

	return false;
}