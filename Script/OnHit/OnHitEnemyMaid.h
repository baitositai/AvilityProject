#pragma once
#include "OnHitEnemy.h"

class EnemyMaid;

class OnHitEnemyMaid : public OnHitEnemy
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	OnHitEnemyMaid(EnemyMaid& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~OnHitEnemyMaid() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="opponentCollider">衝突相手のコライダー</param>
	void Update(const std::weak_ptr<ColliderBase>& opponentCollider);

private:

	// 所有者
	EnemyMaid& owner_;

	// 衝突後処理
	void OnHitItemFood(const std::weak_ptr<ColliderBase>& opponentCollider);
};