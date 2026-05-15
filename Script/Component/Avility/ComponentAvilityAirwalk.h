#pragma once
#include "ComponentAvilityBase.h"
class ComponentAvilityAirwalk : public ComponentAvilityBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	ComponentAvilityAirwalk(Player& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ComponentAvilityAirwalk();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;
};