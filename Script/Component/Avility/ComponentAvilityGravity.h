#pragma once
#include "ComponentAvilityBase.h"

class ComponentAvilityGravity : public ComponentAvilityBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ComponentAvilityGravity(Player& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ComponentAvilityGravity() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

private:

	// 入力のクールタイム
	static constexpr float COOL_TIME = 0.5f;

	// 入力のクールタイム
	float coolTime_;

	// 重力制御処理
	void ProcessGravity();

};