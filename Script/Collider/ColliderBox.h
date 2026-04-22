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
	/// <param name="topPos">ボックスサイズ</param>
	ColliderBox(ActorBase& owner, const CollisionTags::TAG tag, const Vector2& boxSize,float& degAngle);
	
	/// <summary>
	/// デストラクタ
	/// </summary>
	~ColliderBox() override;

	/// <summary>
	/// 自身の複製を生成
	/// </summary>
	/// <returns>複製したインスタンス</returns>
	std::shared_ptr<ColliderBase> Clone() const override;

	/// <summary>
	/// ボックスサイズの設定
	/// </summary>
	/// <param name="topPos">ボックスサイズ</param>
	void SetBoxSize(const Vector2& topPos) { boxSize_ = topPos; }

	/// <summary>
	/// ボックスサイズを返す
	/// </summary>
	/// <returns>ボックスサイズ</returns>
	const Vector2& GetBoxSize() const { return boxSize_; }

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

	/// <summary>
	/// デバッグ描画
	/// </summary>
	void DebugDraw() override;

private:

	// ボックスサイズ
	Vector2 boxSize_;

	// ハーフサイズ
	Vector2 boxHalfSize_;

	//角度(デグリー)
	const float& degAngle_;
};