#pragma once
#include "ComponentAvilityBase.h"

class ComponentAvilityAirslash : public ComponentAvilityBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	ComponentAvilityAirslash(Player& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ComponentAvilityAirslash();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;
};