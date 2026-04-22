#pragma once
#include <vector>
#include "../Common/Vector2.h"
#include "../Collider/ColliderArray.h"

class UtilityCollision
{
public:

	/// <summary>
	/// 配列と円の衝突判定
	/// </summary>
	/// <param name="arrayOfArrays">配列</param>
	/// <param name="hitIds">衝突するID配列</param>
	/// <param name="chipSize">チップサイズ</param>
	/// <param name="result">衝突結果</param>
	/// <param name="circlePos">円の座標</param>
	/// <param name="radius">半径</param>
	/// <returns>判定結果</returns>
	static bool IsHitArrayToCircle(const std::vector<std::vector<int>>& arrayOfArrays, const std::vector<int>& hitIds, const Vector2& chipSize, ColliderArray::Result& result, const Vector2& circlePos, const float radius);

	/// <summary>
	/// 配列とボックスの衝突判定
	/// </summary>
	/// <param name="arrayOfArrays">配列</param>
	/// <param name="hitIds">衝突するID配列</param>
	/// <param name="chipSize">チップサイズ</param>
	/// <param name="result">衝突結果</param>
	/// <param name="boxTopPos">ボックストップ</param>
	/// <param name="boxBottomPos">ボックスボトム</param>
	/// <returns>判定結果</returns>
	static bool IsHitArrayToBox(const std::vector<std::vector<int>>& arrayOfArrays, const std::vector<int>& hitIds, const Vector2& chipSize, ColliderArray::Result& result, const Vector2& boxTopPos, const Vector2& boxBottomPos);

	/// <summary>
	/// 円同士の衝突判定
	/// </summary>
	/// <param name="circlePos1">円1の座標</param>
	/// <param name="radius1">円1の半径</param>
	/// <param name="circlePos2">円2の座標</param>
	/// <param name="radius2">円2の半径</param>
	/// <returns>判定結果</returns>
	static bool IsHitCircleToCircle(const Vector2& circlePos1, const float radius1, const Vector2& circlePos2, const float radius2);

	/// <summary>
	/// 円とボックスの衝突判定
	/// </summary>
	/// <param name="circlePos">円の座標</param>
	/// <param name="radius">半径</param>
	/// <param name="boxTopPos">ボックストップ</param>
	/// <param name="boxBotmPos">ボックスボトム</param>
	/// <returns>判定結果</returns>
	static bool IsHitCircleToBox(const Vector2& circlePos, const float radius, const Vector2& boxTopPos, const Vector2& boxBotmPos);

	/// <summary>
	/// 円とラインの衝突判定
	/// </summary>
	/// <param name="circlePos">円の座標</param>
	/// <param name="radius">半径</param>
	/// <param name="lineTopPos">ライン先端座標</param>
	/// <param name="lineEndPos">ライン末端座標</param>
	/// <returns>判定結果</returns>
	static bool IsHitCircleToLine(const Vector2& circlePos, const float radius, const Vector2& lineTopPos, const Vector2& lineEndPos);

	/// <summary>
	/// ボックス同士の衝突判定
	/// </summary>
	/// <param name="boxTopPos1">ボックス1トップ</param>
	/// <param name="boxBotmPos1">ボックス1ボトム</param>
	/// <param name="boxTopPos2">ボックス2トップ</param>
	/// <param name="boxBotmPos2">ボックス2ボトム</param>
	/// <returns>判定結果</returns>
	static bool IsHitBoxToBox(const Vector2& boxTopPos1, const Vector2& boxBotmPos1, const float degAngle1,
		const Vector2& boxTopPos2, const Vector2& boxBotmPos2, const float degAngle2);

	/// <summary>
	/// ボックスと線の衝突判定
	/// </summary>
	/// <param name="boxTopPos">ボックストップ</param>
	/// <param name="boxBotmPos">ボックスボトム</param>
	/// <param name="lineTopPos">ライン先端座標</param>
	/// <param name="lineEndPos">ライン末端座標</param>
	/// <returns>判定結果</returns>
	static bool IsHitBoxToLine(const Vector2& boxTopPos, const Vector2& boxBotmPos, const Vector2& lineTopPos, const Vector2& lineEndPos);

private:

	// マップチップ番号を取得
	int GetMapChipData(const int x, const int y, const std::vector<int>& hitIds);
};

