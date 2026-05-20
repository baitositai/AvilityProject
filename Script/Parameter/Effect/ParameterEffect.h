#pragma once
#include "../ParameterActor.h"

class ParameterEffect : public ParameterActor
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ParameterEffect();
	
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~ParameterEffect() override;

	/// <summary>
	/// パラメータの読み込み
	/// </summary>
	/// <param name="parameter">パラメータ情報</param>
	void LoadParameter(const Json& parameter) override;

private:

};