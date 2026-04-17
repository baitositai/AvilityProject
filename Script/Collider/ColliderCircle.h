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
	/// <param name="radius">半径</param>
	ColliderCircle(ActorBase& owner, const CollisionTags::TAG tag, const float radius);
	
	/// <summary>
	/// デストラクタ
	/// </summary>
	~ColliderCircle() override;

	/// <summary>
	/// 半径の設定
	/// </summary>
	/// <param name="radius">半径</param>
	void SetRadius(const float radius) { radius_ = radius; }

private:

	// 半径
	float radius_;
};

