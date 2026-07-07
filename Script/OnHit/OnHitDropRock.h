#pragma once
#include "OnHitBase.h"

class GimmickDropRock;

class OnHitDropRock : public OnHitBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	OnHitDropRock(GimmickDropRock& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~OnHitDropRock() override;

private:

	// 所有者
	GimmickDropRock& owner_;

	// タグ別衝突後処理
	void OnHitPlayer(const std::weak_ptr<ColliderBase>& opponentCollider);
	void OnHitPlayerAttack(const std::weak_ptr<ColliderBase>& opponentCollider);
};

