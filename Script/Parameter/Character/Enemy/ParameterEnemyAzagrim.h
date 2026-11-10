#pragma once
#include "ParameterEnemyBoss.h"

class ParameterEnemyAzagrim : public ParameterEnemyBoss
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ParameterEnemyAzagrim();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ParameterEnemyAzagrim() override;

	/// <summary>
	/// 読み込み処理
	/// </summary>
	/// <param name="parameter">パラメータ</param>
	void LoadParameter(const Json& parameter) override;
};

