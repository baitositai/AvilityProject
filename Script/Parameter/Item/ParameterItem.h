#pragma once
#include "../ParameterActor.h"

class ParameterItem : public ParameterActor
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ParameterItem();

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~ParameterItem() override;

	// 描画番号
	int spriteIndex_;
};