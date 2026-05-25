#pragma once
#include "ParameterItem.h"
#include "../../Component/Avility/AvilityTypes.h"

class ParameterItemAvility : public ParameterItem
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ParameterItemAvility();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ParameterItemAvility() override;

	// 種類
	AvilityTypes::TYPE type_;
};