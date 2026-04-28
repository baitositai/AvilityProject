#pragma once
#include "../Component/State/ComponentCharacterStateBase.h"

class CharacterBase;

class ComponentStateDead :  public ComponentCharacterStateBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	ComponentStateDead(CharacterBase& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ComponentStateDead() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

private:

};

