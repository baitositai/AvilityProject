#pragma once
#include "../ComponentCharacterStateBase.h"

class Player;

class ComponentStatePlayerAttack : public ComponentCharacterStateBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	ComponentStatePlayerAttack(Player& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ComponentStatePlayerAttack() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

private:

	// 所有者
	Player& owner_;
};

