#pragma once
#include "EffectBase.h"

class EffectTeleportEnter : public EffectBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ</param>
	EffectTeleportEnter(std::unique_ptr<ParameterEffect> parameter);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EffectTeleportEnter() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

private:

	// パラメータ情報
	ParameterEffect* parameterEffectTeleportEnter_;
};