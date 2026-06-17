#pragma once
#include "OnHitItemBase.h"

class ItemMoney;

class OnHitItemMoney : public OnHitItemBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	OnHitItemMoney(ItemMoney& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~OnHitItemMoney() override;

private:

	// 所有者
	ItemMoney& owner_;

	// タグ別衝突後処理
	void OnHitPlayer(const std::weak_ptr<ColliderBase>& opponentCollider) override;

};

