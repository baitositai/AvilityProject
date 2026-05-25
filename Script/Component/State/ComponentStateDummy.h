#pragma once
#include "../Component/State/ComponentCharacterStateBase.h"

class CharacterBase;

class ComponentStateDummy : public ComponentCharacterStateBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	ComponentStateDummy(CharacterBase& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ComponentStateDummy() override;
};