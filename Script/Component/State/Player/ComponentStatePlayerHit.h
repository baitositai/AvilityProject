#pragma once
#include "../ComponentCharacterStateBase.h"

class Player;

class ComponentStatePlayerHit : public ComponentCharacterStateBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	ComponentStatePlayerHit(Player& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ComponentStatePlayerHit() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

private:
};
