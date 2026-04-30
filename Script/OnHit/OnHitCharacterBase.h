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

	// タグ別衝突後処理
	virtual void OnHitStage(const std::weak_ptr<ColliderBase>& opponentCollider);
	virtual void OnHitAvilityBox(const std::weak_ptr<ColliderBase>& opponentCollider);
	virtual void OnHitAttack(const std::weak_ptr<ColliderBase>& opponentCollider);

private:

	// 所有者
	CharacterBase& owner_;
};

