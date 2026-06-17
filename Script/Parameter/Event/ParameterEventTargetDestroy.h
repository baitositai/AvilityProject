#pragma once
#include "ParameterEvent.h"
#include "../../Common/Vector2.h"

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

	// ターゲットの生成数
	int targetMax_;
	int targetMin_;

	// ターゲットサイズ
	float targetSize_;

	// 生成範囲調整位置
	Vector2 createRangeOffset_;
};