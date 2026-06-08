#pragma once
#include "ParameterEnemy.h"

class ParameterEnemyMaid : public ParameterEnemy
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ParameterEnemyMaid();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ParameterEnemyMaid() override;

	/// <summary>
	/// 読み込み処理
	/// </summary>
	/// <param name="parameter">パラメータ</param>
	void LoadParameter(const Json& parameter) override;

private:


};