#pragma once
#include "../ComponentCharacterStateBase.h"

class Player;

class ComponentStatePlayerRespawn : public ComponentCharacterStateBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	ComponentStatePlayerRespawn(Player& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ComponentStatePlayerRespawn() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

private:
};

