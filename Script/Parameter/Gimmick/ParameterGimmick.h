#pragma once
#include "../ParameterActor.h"

class ParameterGimmick : public ParameterActor
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ParameterGimmick();

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~ParameterGimmick() override;

	/// <summary>
	/// 読み込み
	/// </summary>
	/// <param name="parameter">パラメータ</param>
	virtual void LoadParameter(const Json& parameter) override;

private:

};