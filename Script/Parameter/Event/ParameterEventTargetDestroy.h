#pragma once
#include "ParameterEvent.h"
class ParameterEventTargetDestroy : public ParameterEvent
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ParameterEventTargetDestroy();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ParameterEventTargetDestroy() override;

	/// <summary>
	/// 読み込み
	/// </summary>
	/// <param name="parameter">パラメータ</param>
	void LoadParameter(const Json& parameter) override;
};

