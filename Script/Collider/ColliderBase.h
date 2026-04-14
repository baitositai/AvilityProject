#pragma once
#include "../Manager/Game/CollisionTags.h"

class ActorBase;

class ColliderBase
{
public: 

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	/// <param name="tag">衝突判定タグ</param>
	ColliderBase(const ActorBase& owner, const CollisionTags::TAG tag);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~ColliderBase();

protected:	
	
	// タグ
	const CollisionTags::TAG TAG;

	// オーナー
	const ActorBase& owner_;
};