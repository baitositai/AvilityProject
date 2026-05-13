#pragma once
#include "ComponentBase.h"

class CharacterBase;

class ComponentKnockBack : public ComponentBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	ComponentKnockBack(CharacterBase& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ComponentKnockBack() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

private:

	// ノックバック速度が毎秒どれだけ減衰するか
	static constexpr float KNOCK_BACK_DECELERATION = 1200.0f;

	// 所有者
	CharacterBase& owner_;
};

