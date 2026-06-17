#pragma once
#include "OnHitBase.h"

class ItemBase;
class InputManager;

class OnHitItemBase : public OnHitBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	OnHitItemBase(ItemBase& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~OnHitItemBase() override;

protected:

	// 入力の参照
	InputManager& inputManager_;
	
private:

	// 所有者
	ItemBase& owner_;

	// タグ別衝突後処理
	virtual void OnHitPlayer(const std::weak_ptr<ColliderBase>& opponentCollider);
};