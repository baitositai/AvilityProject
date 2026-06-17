#pragma once
#include "OnHitBase.h"

class GimmickTarget;

class OnHitTarget : public OnHitBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	OnHitTarget(GimmickTarget& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~OnHitTarget() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update(const std::weak_ptr<ColliderBase>& opponentCollider) override;

private:

	// 所有者
	GimmickTarget& owner_;
};