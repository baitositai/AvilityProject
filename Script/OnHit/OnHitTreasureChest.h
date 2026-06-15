#pragma once
#include "OnHitBase.h"

class GimmickTreasureChest;

class OnHitTreasureChest : public OnHitBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	OnHitTreasureChest(GimmickTreasureChest& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~OnHitTreasureChest() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="opponentCollider">衝突相手のコライダー</param>
	void Update(const std::weak_ptr<ColliderBase>& opponentCollider) override;

private:

	// 所有者
	GimmickTreasureChest& owner_;
};