#pragma once
#include "OnHitEnemy.h"

class EnemyPanda;

class OnHitPanda : public OnHitEnemy
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	OnHitPanda(EnemyPanda& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~OnHitPanda() override;

private:

	// 所有者
	EnemyPanda& owner_;
	
	// プレイヤーの攻撃の衝突後処理
	void OnHitPlayerAttack(const std::weak_ptr<ColliderBase>& opponentCollider) override;
};

