#pragma once
#include "../ActorBase.h"
#include "../../Parameter/Effect/ParameterEffect.h"

class EffectBase : public ActorBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメーター</param>
	explicit EffectBase(std::unique_ptr<ParameterEffect> parameter);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~EffectBase() override;

	/// <summary>
	/// パラメーターを返す(変更可)
	/// </summary>
	/// <returns>パラメータ</returns>
	ParameterEffect& GetParameter() { return *parameterEffect_; }

	/// <summary>
	/// パラメータを返す
	/// </summary>
	/// <returns>パラメータ</returns>
	const ParameterEffect& GetParameter() const { return *parameterEffect_; }

protected:

	// 型変換用のパラメータを返す関数
	ParameterEffect* GetParameterEffectPtr() { return parameterEffect_; }

private:

	// パラメータ情報
	ParameterEffect* parameterEffect_;

};