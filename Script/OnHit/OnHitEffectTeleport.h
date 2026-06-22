#pragma once
#include "OnHitEffect.h"
class OnHitEffectTeleport : public OnHitEffect
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	OnHitEffectTeleport(EffectBase& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~OnHitEffectTeleport() override;

private:

	// 所有者
	EffectBase& owner_;

	// タグ別衝突後処理
	void OnHitEnemy(const std::weak_ptr<ColliderBase>& opponentCollider) override;
};

