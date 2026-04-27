#pragma once
#include "OnHitCharacterBase.h"

class Player;

class OnHitPlayer : public OnHitCharacterBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	OnHitPlayer(Player& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~OnHitPlayer() override;

private:

	// 所有者
	Player& owner_;

	// タグ別衝突後処理
	void OnHitStage(const std::weak_ptr<ColliderBase>& opponentCollider) override;

	// アビリティ別の衝突後処理
	void AvilityShot(const std::weak_ptr<ColliderBase>& opponentCollider, const Vector2F& normal);

};

