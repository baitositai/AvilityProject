#pragma once
#include "OnHitCharacterBase.h"

class EnemyBase;
class SceneManager;

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

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="opponentCollider">衝突相手のコライダー</param>
	virtual void Update(const std::weak_ptr<ColliderBase>& opponentCollider) override;

protected:

	// 各種衝突後処理
	virtual void OnHitPlayerAttack(const std::weak_ptr<ColliderBase>& opponentCollider);
	void OnHitPlayerAvilityStamp(const std::weak_ptr<ColliderBase>& opponentCollider);
	void OnHitPlayerAvilityShot(const std::weak_ptr<ColliderBase>& opponentCollider);
	void OnHitOtherEnemy(const std::weak_ptr<ColliderBase>& opponentCollider);
	void OnHitItemTreasure(const std::weak_ptr<ColliderBase>& opponentCollider);

	// 視野角の衝突後処理
	void OnHitEnemyViewToPlayer(const std::weak_ptr<ColliderBase>& opponentCollider);

private:

	static constexpr float SHOT_DAMAGE_INTERVAL = 0.1f;

	// シーンの参照
	SceneManager& sceneManager_;

	// ショットでのダメージインターバル
	float shotDamageInterval_;

	// 所有者
	EnemyBase& owner_;
};