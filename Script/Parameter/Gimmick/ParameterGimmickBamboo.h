#pragma once
#include "ParameterGimmick.h"

class ParameterGimmickBamboo : public ParameterGimmick
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ParameterGimmickBamboo();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ParameterGimmickBamboo() override;

	/// <summary>
	/// 読み込み
	/// </summary>
	/// <param name="parameter">パラメータ</param>
	void LoadParameter(const Json& parameter) override;

};