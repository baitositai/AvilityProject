#pragma once
#include "ParameterEvent.h"
#include "../../Common/Vector2.h"

class ParameterEventTimeLimitDefeatAll : public ParameterEvent
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ParameterEventTimeLimitDefeatAll();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ParameterEventTimeLimitDefeatAll() override;

	/// <summary>
	/// 読み込み
	/// </summary>
	/// <param name="parameter">パラメータ</param>
	void LoadParameter(const Json& parameter) override;

	// 敵の生成ウェーブ数
	int waveMax_;
	int waveMin_;

	// 敵の生成数
	int enemyNumMax_;
	int enemyNumMin_;

	// チャレンジ時間
	float challengeTime_;

	// 終了後時間
	float endTime_;

	// 生成範囲
	Vector2 createRange_;

	// 左上座標
	Vector2 createLeftTopPos_;
};