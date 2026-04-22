#pragma once
#include "../ComponentBase.h"

class CharacterBase;

class ComponentActionBase : public ComponentBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ComponentActionBase(CharacterBase& owner);
	
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~ComponentActionBase() override;

protected:

};

