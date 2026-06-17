#pragma once
#include "OnHitItemBase.h"

class ItemTreasure;

class OnHitItemTreasure : public OnHitItemBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	OnHitItemTreasure(ItemTreasure& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~OnHitItemTreasure() override;

private:

	// 所有者
	ItemTreasure& owner_;

	// タグ別衝突後処理
	void OnHitPlayer(const std::weak_ptr<ColliderBase>& opponentCollider) override;
};

