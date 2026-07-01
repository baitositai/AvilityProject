#pragma once
#include "ParameterEnemyBoss.h"

class ParameterEnemyPanda : public ParameterEnemyBoss
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ParameterEnemyPanda();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ParameterEnemyPanda() override;

	/// <summary>
	/// 読み込み処理
	/// </summary>
	/// <param name="parameter">パラメータ</param>
	void LoadParameter(const Json& parameter) override;

	// 各攻撃の開始フレーム
	int defaultAttackStartFrame2_;
	int defaultAttackStartFrame3_;
	int defaultAttackStartFrame4_;

};