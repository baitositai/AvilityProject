#pragma once
#include "ParameterEnemyBoss.h"

class ParameterEnemyMaid : public ParameterEnemyBoss
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

	// 食べ物の取得回数
	int hitFoodCount_;

	// 条件食べ物の取得回数
	int triggerFoodCount_;
};