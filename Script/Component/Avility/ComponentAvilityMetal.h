#pragma once
#include "./ComponentAvilityBase.h"

class Player;

class ComponentAvilityMetal : public ComponentAvilityBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ComponentAvilityMetal(Player& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ComponentAvilityMetal() override;

	/// <summary>
	/// 取り外し時の処理
	/// </summary>
	void Remove() override;

private:
	
	// 重力の追加上昇率
	static constexpr float GRAVITY_BOOST_RATE = 0.2;

	// ダメージの軽減率
	static constexpr float ADD_DAMAGE_RATE = 0.5f;

};