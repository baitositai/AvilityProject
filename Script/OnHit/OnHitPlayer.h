#pragma once
#include "OnHitBase.h"

class Player;

class OnHitPlayer : public OnHitBase
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
	void OnHitStage(const std::weak_ptr<ColliderBase>& opponentCollider);
	void OnHitAvilityBox(const std::weak_ptr<ColliderBase>& opponentCollider);
};

