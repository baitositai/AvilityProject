#pragma once
#include <set>
#include <vector>
#include "ColliderBase.h"
#include "../Common/Vector2.h"

class ColliderArray : public ColliderBase
{
public:

	// 衝突判定の結果
	struct Result
	{
		Vector2 hitIndex;
		std::vector<Vector2> hitIndexes;
	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	/// <param name="tag">タグ</param>
	/// <param name="arrayOfArrays">衝突判定を行う配列</param>
	/// <param name="hitIds">衝突判定を返すID配列</param>
	/// <param name="chipSize">チップサイズ</param>
	ColliderArray(ActorBase& owner, const CollisionTags::TAG tag, const std::vector<std::vector<int>>& arrayOfArrays, const std::vector<int>& hitIds, const Vector2& chipSize);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ColliderArray() override;

	/// <summary>
	/// 自身の複製を生成
	/// </summary>
	/// <returns>複製したインスタンス</returns>
	std::shared_ptr<ColliderBase> Clone() const override;

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
	/// 衝突判定結果のリセット
	/// </summary>
	void ResetResult();

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

	/// <summary>
	/// チップサイズを返す
	/// </summary>
	/// <returns>チップサイズ</returns>
	const Vector2& GetChipSize() const { return chipSize_; }

	/// <summary>
	/// デバッグ描画
	/// </summary>
	void DebugDraw() override;

private:

	// 衝突判定を行う配列
	std::vector<std::vector<int>> arrayOfArrays_;

	// 衝突判定を返すID配列
	std::vector<int> hitIds_;

	// チップサイズ
	Vector2 chipSize_;

	// 判定結果
	Result result_;

};