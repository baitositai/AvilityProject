#pragma once
#include "ParameterGimmick.h"

class ParameterGimmickGrowingBamboo : public ParameterGimmick
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ParameterGimmickGrowingBamboo();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ParameterGimmickGrowingBamboo() override;

	/// <summary>
	/// 読み込み
	/// </summary>
	/// <param name="parameter">パラメータ</param>
	void LoadParameter(const Json& parameter) override;

	// 最大成長回数
	int growCountMax_;

	// 成長インターバル
	float growIntervalTime_;

	// 削除待機時間
	float deleteWaitTime_;
};

