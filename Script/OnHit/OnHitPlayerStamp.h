#pragma once
#include "OnHitCharacterBase.h"

class Player;

class OnHitPlayerStamp : public OnHitCharacterBase
{
public:
	
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	OnHitPlayerStamp(Player& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~OnHitPlayerStamp();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update(const std::weak_ptr<ColliderBase>& opponentCollider) override;

private:

	// 無敵時間
	static constexpr float INVINCIBLE_TIME = 0.1f;

	// 所有者
	Player& owner_;

};

