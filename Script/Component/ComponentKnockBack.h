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

	CharacterBase& owner_;
};

