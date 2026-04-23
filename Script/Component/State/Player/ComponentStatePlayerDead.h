#pragma once
#include "../ComponentCharacterStateBase.h"

class Player;

class ComponentStatePlayerDead : public ComponentCharacterStateBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	ComponentStatePlayerDead(Player& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ComponentStatePlayerDead() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

private:
};

