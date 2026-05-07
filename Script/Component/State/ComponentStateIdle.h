#pragma once
#include "../Component/State/ComponentCharacterStateBase.h"

class CharacterBase;

class ComponentStateIdle : public ComponentCharacterStateBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	ComponentStateIdle(CharacterBase& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ComponentStateIdle() override;
};

