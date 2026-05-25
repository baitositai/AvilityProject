#pragma once
#include "OnHitBase.h"

class EffectBase;

class OnHitEffect : public OnHitBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	OnHitEffect(EffectBase& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~OnHitEffect() override;

private:

	// 所有者
	EffectBase& owner_;

	// タグ別衝突後処理
	virtual void OnHitEnemy(const std::weak_ptr<ColliderBase>& opponentCollider);

};

