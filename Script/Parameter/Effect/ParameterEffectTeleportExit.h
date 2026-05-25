#pragma once
#include "ParameterEffect.h"
#include "../Effect/ParameterEffectTeleportExit.h"

class ParameterEffectTeleportExit : public ParameterEffect
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ</param>
	ParameterEffectTeleportExit();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ParameterEffectTeleportExit() override;

	/// <summary>
	/// パラメータの読み込み
	/// </summary>
	/// <param name="parameter">パラメータ情報</param>
	void LoadParameter(const Json& parameter) override;

private:


};

