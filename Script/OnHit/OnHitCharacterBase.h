#pragma once
#include "OnHitBase.h"
#include "../Common/Vector2F.h"

class CharacterBase;

class OnHitCharacterBase : public OnHitBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	OnHitCharacterBase(CharacterBase& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~OnHitCharacterBase() override;

protected:
	
	// ノックバックの力
	const Vector2F KNOCK_BACK_FORCE = { 800.0f, 800.0f };	

	// ノックバックの強め
	const Vector2F KNOCK_BACK_FORCE_STRONG = { 1200.0f, 1200.0f };

	// タグ別衝突後処理
	virtual void OnHitStage(const std::weak_ptr<ColliderBase>& opponentCollider);
	virtual void OnHitAvilityBox(const std::weak_ptr<ColliderBase>& opponentCollider);
	virtual void OnHitAttack(const std::weak_ptr<ColliderBase>& opponentCollider);

	// ダメージ処理(倒しきれた場合trueを返す)
	bool Damage(const std::weak_ptr<ColliderBase>& opponentCollider, int damage = -1);
	
	// ノックバック処理
	void KnockBack(const std::weak_ptr<ColliderBase>& opponentCollider, const Vector2F& knockBackForce);

private:

	// 所有者
	CharacterBase& owner_;
};