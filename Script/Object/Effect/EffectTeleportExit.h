#pragma once
#include "../Effect/EffectBase.h"
#include "../../Parameter/Effect/ParameterEffectTeleportExit.h"

class ParameterEffectTeleportExit;

class EffectTeleportExit : public EffectBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ</param>
	explicit EffectTeleportExit(std::unique_ptr<ParameterEffectTeleportExit> parameter);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EffectTeleportExit() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

private:

	bool isAttack_;

	// パラメータ情報
	ParameterEffectTeleportExit* parameterEffectTeleportExit_;

};