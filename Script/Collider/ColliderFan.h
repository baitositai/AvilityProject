#pragma once
#include "ColliderBase.h"

class ColliderFan : public ColliderBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	/// <param name="tag">タグ</param>
	/// <param name="followPos">追従座標</param>
	/// <param name="radius">視野角半径</param>
	/// <param name="baseAngle">基本角</param>
	/// <param name="viewAngle">視野角</param>
	ColliderFan(ActorBase& owner, const CollisionTags::TAG tag, Vector2F& followPos, float& baseAngle, float& radius, float& viewAngle);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ColliderFan() override;

	/// <summary>
	/// デバッグ描画
	/// </summary>
	void DebugDraw() override;

	/// <summary>
	/// 自身の複製を生成
	/// </summary>
	/// <returns>複製したインスタンス</returns>
	std::shared_ptr<ColliderBase> Clone() const override;

	/// <summary>
	/// 半径を返す
	/// </summary>
	/// <returns>半径</returns>
	const float GetRadius() const { return radius_; }

	/// <summary>
	/// 視野角度を返す
	/// </summary>
	/// <returns>視野角度</returns>
	const float GetViewAngle() const { return viewAngle_; }

	/// <summary>
	/// ベース角度を返す	
	/// </summary>
	/// <returns>ベース角度</returns>
	const float GetBaseAngle() const { return baseAngle_; }

private:

	// ベース角度
	float& baseAngle_;

	// 視野角半径
	float& radius_;

	// 視野角
	float& viewAngle_;

};