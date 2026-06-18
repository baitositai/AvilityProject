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
	/// 生成処理
	/// </summary>
	void Create() override;

	/// <summary>
	/// 初期化
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;
};