#pragma once
#include "OnHitCharacterBase.h"

class EnemyBase;

class OnHitEnemy : public OnHitCharacterBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	OnHitEnemy(EnemyBase& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~OnHitEnemy() override;

private:

	// 所有者
	EnemyBase& owner_;

	// 各種衝突後処理
	void OnHitPlayerAttack(const std::weak_ptr<ColliderBase>& opponentCollider);
	void OnHitPlayerAvilityStamp(const std::weak_ptr<ColliderBase>& opponentCollider);
	void OnHitOtherEnemy(const std::weak_ptr<ColliderBase>& opponentCollider);
};