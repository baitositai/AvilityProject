#pragma once
#include "ComponentAvilityBase.h"
class ComponentAvilitySuperman : public ComponentAvilityBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	ComponentAvilitySuperman(Player& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ComponentAvilitySuperman() override;

	/// <summary>
	/// 取り外し処理
	/// </summary>
	void Remove() override;

private:

	// 最大ジャンプ量の追加量
	static constexpr float ADD_JUMP_POWER_MAX = 10.0f; 

	// 移動速度の上昇率
	static constexpr float ADD_MOVE_SPEED_BOOST_RATE = 0.5f;

	// 攻撃力の上昇率
	static constexpr float ADD_ATTACK_POWER_BOOST_RATE = 0.5f;
};