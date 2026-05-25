#pragma once
#include "OnHitBase.h"

class ItemBase;

class OnHitItem : public OnHitBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	OnHitItem(ItemBase& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~OnHitItem() override;

private:
	
	// 所有者
	ItemBase& owner_;

	// タグ別衝突後処理
	void OnHitPlayer(const std::weak_ptr<ColliderBase>& opponentCollider);

};

