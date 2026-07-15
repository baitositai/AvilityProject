#pragma once
#include "OnHitBase.h"

class GimmickGroundRock;

class OnHitGroundRock :
    public OnHitBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	OnHitGroundRock(GimmickGroundRock& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~OnHitGroundRock() override;

private:

	// 所有者
	GimmickGroundRock& owner_;

	// タグ別衝突後処理
	void OnHitPlayer(const std::weak_ptr<ColliderBase>& opponentCollider);
};

