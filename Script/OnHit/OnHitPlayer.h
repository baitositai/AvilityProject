#pragma once
#include <memory>
#include "OnHitCharacterBase.h"

class Player;
class FactoryComponent;
class OnHitPlayerStamp;

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

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="opponentCollider">衝突相手のコライダー</param>
	void Update(const std::weak_ptr<ColliderBase>& opponentCollider) override;

private:

	// 所有者
	Player& owner_;

	// コンポーネント生成クラス
	FactoryComponent& factoryComponent_;

	// スタンプ用の衝突後処理
	std::unique_ptr<OnHitPlayerStamp> onHitPlayerStamp_;

	// タグ別衝突後処理
	void OnHitStage(const std::weak_ptr<ColliderBase>& opponentCollider) override;
	void OnHitEnemy(const std::weak_ptr<ColliderBase>& opponentCollider);
	void OnHitItemAvility(const std::weak_ptr<ColliderBase>& opponentCollider);

	// アビリティ別の衝突後処理
	void AvilityShot(const std::weak_ptr<ColliderBase>& opponentCollider, const Vector2F& normal);
};