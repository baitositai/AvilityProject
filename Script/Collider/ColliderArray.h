#pragma once
#include <set>
#include <vector>
#include "ColliderBase.h"

class ColliderArray : public ColliderBase
{
public:

	// 衝突判定の結果
	struct Result
	{
		bool isHit_ = false;			// 衝突判定
		bool isHitWall_ = false;		// 壁判定
		bool isHitFloor_ = false;		// 床判定
		bool isHitCeiling_ = false; 	// 天井判定
		float pushOutX_ = 0.0f;			// Xの押し出し量
		float pushOutY_ = 0.0f;			// Yの押し出し量
	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	/// <param name="tag">タグ</param>
	/// <param name="arrayOfArrays">衝突判定を行う配列</param>
	/// <param name="hitIds">衝突判定を返すID配列</param>
	ColliderArray(ActorBase& owner, const CollisionTags::TAG tag, const std::vector<std::vector<int>>& arrayOfArrays, const std::vector<int>& hitIds);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ColliderArray();

	/// <summary>
	/// 衝突判定を行う配列を設定
	/// </summary>
	/// <param name="arrayOfArrays">衝突判定を行う配列</param>
	void SetArrayOfArrays(const std::vector<std::vector<int>>& arrayOfArrays) { arrayOfArrays_ = arrayOfArrays; }

	/// <summary>
	/// 衝突判定を返すID配列を設定
	/// </summary>
	/// <param name="hitIds">衝突判定を返すID配列</param>
	void SetHitIds(const std::vector<int>& hitIds) { hitIds_ = hitIds; }

	/// <summary>
	/// 衝突判定の結果を設定
	/// </summary>
	/// <param name="result">衝突判定の結果</param>
	void SetResult(const Result& result) { result_ = result; }

	/// <summary>
	/// 衝突判定を行う配列を返す
	/// </summary>
	/// <returns>衝突判定を行う配列</returns>
	const std::vector<std::vector<int>>& GetArrayOfArrys() const { return arrayOfArrays_; }

	/// <summary>
	/// 衝突判定を返すID配列を返す
	/// </summary>
	/// <returns>衝突判定を返すID配列</returns>
	const std::vector<int> GetHitIds() const { return hitIds_; }

	/// <summary>
	/// 衝突判定の結果を返す
	/// </summary>
	/// <returns>衝突判定の結果</returns>
	const Result& GetResult() const { return result_; }

private:

	// 衝突判定を行う配列
	std::vector<std::vector<int>> arrayOfArrays_;

	// 衝突判定を返すID配列
	std::vector<int> hitIds_;

	// 判定結果
	Result result_;

};