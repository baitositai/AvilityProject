#pragma once
#include "ParameterEnemy.h"

class ParameterEnemyPanda : public ParameterEnemy
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

private:


};