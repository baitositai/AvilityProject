#pragma once
#include <set>
#include <vector>
#include "ColliderBase.h"
#include "../Common/Vector2.h"

class ColliderArray : public ColliderBase
{
public:

	// 接触種類
	enum class HIT_TYPE
	{
		FLOOR,							// 床
		WALL,							// 壁
		CEILING							// 天井
	};

	// 判定結果
	struct Result
	{
		bool hit = false;				// 衝突したか
		Vector2 hitChipIndex = {};		// 衝突したタイルのインデックス
		Vector2 chipSize = {};			// チップサイズ
	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	/// <param name="tag">タグ</param>
	/// <param name="followPos">追従対象の座標</param>
	/// <param name="arrayOfArrays">衝突判定を行う配列</param>
	/// <param name="passIndexs">すり抜け床配列</param>
	/// <param name="chipSize">チップサイズ</param>
	ColliderArray(ActorBase& owner, const CollisionTags::TAG tag, Vector2F& followPos, const std::vector<std::vector<int>>& arrayOfArrays, const std::vector<int>& passIndexs, const Vector2& chipSize);

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
	/// 座標が衝突しているか判定
	/// </summary>
	/// <param name="worldPos">ワールド座標</param>
	/// <param name="isXAxis">横軸判定</param>
	/// <param name="stepMove">移動量</param>
	/// <returns>衝突結果</returns>
	Result CheckHitMapChip(const Vector2& worldPos, bool isXAxis, float stepMove) const;

	/// <summary>
	/// 衝突判定を行う配列を設定
	/// </summary>
	/// <param name="arrayOfArrays">衝突判定を行う配列</param>
	void SetArrayOfArrays(const std::vector<std::vector<int>>& arrayOfArrays) { arrayOfArrays_ = arrayOfArrays; }

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

	// 下からすり抜ける床の配列
	std::vector<int> passIndexes_;

	// チップサイズ
	Vector2 chipSize_;

	// 判定結果
	Result result_;
};