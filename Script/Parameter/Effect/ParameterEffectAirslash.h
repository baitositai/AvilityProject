#pragma once
#include "ParameterEffect.h"

class ParameterEffectAirslash : public ParameterEffect
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ParameterEffectAirslash();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ParameterEffectAirslash() override;

	/// <summary>
	/// パラメータの読み込み
	/// </summary>
	/// <param name="parameter">パラメータ情報</param>
	void LoadParameter(const Json& parameter) override;

private:

};