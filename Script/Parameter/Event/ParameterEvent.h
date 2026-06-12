#pragma once
#include "../ParameterBase.h"

class ParameterEvent : public ParameterBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ParameterEvent();
	
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~ParameterEvent() override;

	/// <summary>
	/// 読み込み
	/// </summary>
	/// <param name="parameter">パラメータ</param>
	virtual void LoadParameter(const Json& parameter) override;

	// チャレンジ時間
	float challengeTime_;

	// 終了後時間
	float endTime_;
};