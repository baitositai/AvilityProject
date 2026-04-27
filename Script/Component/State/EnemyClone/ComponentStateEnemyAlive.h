#pragma once
#include "../../ComponentBase.h"

class CharacterBase;

class ComponentStateEnemyAlive : public ComponentBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	ComponentStateEnemyAlive(CharacterBase& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ComponentStateEnemyAlive() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

private:

	CharacterBase& owner_;
};

