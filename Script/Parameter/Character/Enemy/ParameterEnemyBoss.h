#pragma once
#include "ParameterEnemy.h"

class ParameterEnemyBoss : public ParameterEnemy
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ParameterEnemyBoss();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ParameterEnemyBoss() override;

	/// <summary>
	/// 読み込み処理
	/// </summary>
	/// <param name="parameter">パラメータ情報</param>
	void LoadParameter(const Json& parameter) override;

	// ボスUIネームプレートインデックス
	int bossUiNamePlateIndex_;

};

