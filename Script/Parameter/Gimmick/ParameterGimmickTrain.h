#pragma once
#include "ParameterGimmick.h"

class ParameterGimmickTrain : public ParameterGimmick
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ParameterGimmickTrain();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ParameterGimmickTrain() override;

	/// <summary>
	/// 読み込み
	/// </summary>
	/// <param name="parameter">パラメータ</param>
	void LoadParameter(const Json& parameter) override;

	float waitTimeMax_;
	float waitTimeMin_;

};