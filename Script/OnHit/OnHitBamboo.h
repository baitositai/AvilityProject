#pragma once
#include "OnHitBase.h"

class GimmickBamboo;

class OnHitBamboo : public OnHitBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	OnHitBamboo(GimmickBamboo& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~OnHitBamboo() override;

private:

	// 所有者
	GimmickBamboo& owner_;

	// タグ別衝突後処理
	void OnHitPlayer(const std::weak_ptr<ColliderBase>& opponentCollider);
	void OnHitPlayerAttack(const std::weak_ptr<ColliderBase>& opponentCollider);
};