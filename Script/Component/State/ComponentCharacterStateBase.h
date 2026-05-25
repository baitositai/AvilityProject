#pragma once
#include "../ComponentBase.h"
#include "../../Object/Character/CharacterBase.h"

class ComponentCharacterStateBase : public ComponentBase
{
public:
	
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	ComponentCharacterStateBase(CharacterBase& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~ComponentCharacterStateBase() override;

private:

};