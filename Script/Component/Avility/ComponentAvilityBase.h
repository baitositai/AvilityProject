#pragma once
#include "../ComponentBase.h"

class Player;

class ComponentAvilityBase : public ComponentBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	ComponentAvilityBase(Player& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~ComponentAvilityBase() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update() override;

protected:

	Player& owner_;

};

