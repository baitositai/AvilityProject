#pragma once
#include "EnemyBase.h"
#include "../../../Parameter/Character/Enemy/ParameterEnemyPanda.h"

class EnemyPanda : public EnemyBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ</param>
	explicit EnemyPanda(std::unique_ptr<ParameterEnemyPanda> parameter);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyPanda() override;

private:

	// パラメータ情報
	ParameterEnemyPanda* parameterEnemyPanda_;
};

