#pragma once
#include "OnHitCharacterBase.h"

class EnemyClone;

class OnHitEnemyClone : public OnHitCharacterBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	OnHitEnemyClone(EnemyClone& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~OnHitEnemyClone() override;

private:

	// 所有者
	EnemyClone& owner_;



};

