#pragma once
#include "ColliderBase.h"
#include "../Common/Vector2.h" 

class ColliderLine : public ColliderBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	/// <param name="tag">タグ</param>
	/// <param name="topPos">先端座標</param>
	/// <param name="endPos">末端座標</param>
	ColliderLine(ActorBase& owner, const CollisionTags::TAG tag, const Vector2& topPos, const Vector2& endPos);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ColliderLine() override;

	/// <summary>
	/// 自身の複製を生成
	/// </summary>
	/// <returns>複製したインスタンス</returns>
	std::shared_ptr<ColliderBase> Clone() const override;

	/// <summary>
	/// 先端座標の設定
	/// </summary>
	/// <param name="topPos">先端座標</param>
	void SetTopPos(const Vector2& topPos) { topPos_ = topPos; }

	/// <summary>
	/// 末端座標の設定
	/// </summary>
	/// <param name="endPos">末端座標</param>
	void SetEndPos(const Vector2& endPos) { endPos_ = endPos; }

	/// <summary>
	/// 先端座標を返す
	/// </summary>
	/// <returns>先端座標</returns>
	const Vector2& GetTopPos() const { return topPos_; }

	/// <summary>
	/// 末端座標
	/// </summary>
	/// <returns>末端座標</returns>
	const Vector2& GetEndPos() const { return endPos_; }

	/// <summary>
	/// 先端座標の相対位置を返す
	/// </summary>
	/// <returns>先端座標の相対位置</returns>
	const Vector2& GetLocalTopPos() const;

	/// <summary>
	/// 末端座標の相対位置を返す
	/// </summary>
	/// <returns>末端座標の相対位置</returns>
	const Vector2& GetLocalEndPos() const;

private:
	
	// 先端座標
	Vector2 topPos_;

	// 末端座標
	Vector2 endPos_;
};

