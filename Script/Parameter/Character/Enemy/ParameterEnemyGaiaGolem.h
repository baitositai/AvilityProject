#pragma once
#include "ParameterEnemyBoss.h"
class ParameterEnemyGaiaGolem :
    public ParameterEnemyBoss
{
public:

    /// <summary>
    /// コンストラクタ
    /// </summary>
    ParameterEnemyGaiaGolem();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ParameterEnemyGaiaGolem() override;

	/// <summary>
	/// 読み込み処理
	/// </summary>
	/// <param name="parameter">パラメータ</param>
	void LoadParameter(const Json& parameter) override;
private:
};

