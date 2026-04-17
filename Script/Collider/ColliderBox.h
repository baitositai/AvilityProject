#pragma once
#include "ColliderBase.h"
#include "../Common/Vector2.h"

class ColliderBox : public ColliderBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	/// <param name="tag">衝突判定タグ</param>
	/// <param name="topPos">右上座標</param>
	/// <param name="endPos">左下座標</param>
	ColliderBox(ActorBase& owner, const CollisionTags::TAG tag, const Vector2& topPos, const Vector2& bottomPos);
	
	/// <summary>
	/// デストラクタ
	/// </summary>
	~ColliderBox() override;

	/// <summary>
	/// 右上座標の設定
	/// </summary>
	/// <param name="topPos">右上座標</param>
	void SetTopPos(const Vector2& topPos) { topPos_ = topPos; }

	/// <summary>
	/// 左下座標の設定
	/// </summary>
	/// <param name="endPos">左下座標</param>
	void SetBottomPos(const Vector2& bottomPos) { bottomPos_ = bottomPos; }

	/// <summary>
	/// 右上座標を返す
	/// </summary>
	/// <returns>右上座標</returns>
	const Vector2& GetTopPos() const { return topPos_; }

	/// <summary>
	/// 左下座標
	/// </summary>
	/// <returns>左下座標</returns>
	const Vector2& GetBottomPos() const { return bottomPos_; }

	/// <summary>
	/// 右上座標の相対位置を返す
	/// </summary>
	/// <returns>右上座標の相対位置</returns>
	const Vector2& GetLocalTopPos() const;

	/// <summary>
	/// 左下座標の相対位置を返す
	/// </summary>
	/// <returns>左下座標の相対位置</returns>
	const Vector2& GetLocalBottomPos() const;

private:

	// 右上座標
	Vector2 topPos_;

	// 左下座標
	Vector2 bottomPos_;
};