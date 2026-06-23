#pragma once
#include "ParameterGimmick.h"

class ParameterGimmickSpeechBubble : public ParameterGimmick
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ParameterGimmickSpeechBubble();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ParameterGimmickSpeechBubble() override;

	/// <summary>
	/// 読み込み
	/// </summary>
	/// <param name="parameter">パラメータ</param>
	void LoadParameter(const Json& parameter) override;

	// 通常表示時間
	float displayTime_;

	// 吹き出し拡大速度
	float scaleUpSpeed_;
};