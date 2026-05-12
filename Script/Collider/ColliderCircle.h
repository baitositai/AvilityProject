#pragma once
#include "ColliderBase.h"

class ColliderCircle : public ColliderBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	/// <param name="tag">タグ</param>
	/// <param name="followPos">追従対象の座標</param>
	/// <param name="radius">半径</param>
	ColliderCircle(ActorBase& owner, const CollisionTags::TAG tag, Vector2F& followPos, const float radius);
	
	/// <summary>
	/// デストラクタ
	/// </summary>
	~ColliderCircle() override;

	/// <summary>
	/// 自身の複製を生成
	/// </summary>
	/// <returns>複製したインスタンス</returns>
	std::shared_ptr<ColliderBase> Clone() const override;

	/// <summary>
	/// 半径の設定
	/// </summary>
	/// <param name="radius">半径</param>
	void SetRadius(const float radius) { radius_ = radius; }

	/// <summary>
	/// 半径を返す
	/// </summary>
	/// <returns>半径</returns>
	const float GetRadius() const { return radius_; }

	/// <summary>
	/// デバッグ描画
	/// </summary>
	void DebugDraw() override;

private:

	// 半径
	float radius_;
};

