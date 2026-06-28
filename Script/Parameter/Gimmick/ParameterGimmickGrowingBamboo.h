#pragma once
#include "ParameterGimmick.h"

class ParameterGimmickGrowingBamboo : public ParameterGimmick
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ParameterGimmickGrowingBamboo();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ParameterGimmickGrowingBamboo() override;

	/// <summary>
	/// 読み込み
	/// </summary>
	/// <param name="parameter">パラメータ</param>
	void LoadParameter(const Json& parameter) override;
};

