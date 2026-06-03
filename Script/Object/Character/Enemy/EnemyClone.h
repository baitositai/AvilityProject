#pragma once
#include "EnemyBase.h"

class EnemyClone : public EnemyBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ情報</param>
	explicit EnemyClone(std::unique_ptr<ParameterEnemy> parameter);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyClone() override;

private:

	// パラメータ情報
	ParameterEnemy* parameterEnemyClone_;
};