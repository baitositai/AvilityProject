#pragma once
#include "EnemyBase.h"

class EnemySlime : public EnemyBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ</param>
	EnemySlime(std::unique_ptr<ParameterEnemy> parameter);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemySlime() override;


private:

	ParameterEnemy* parameterEnemySlime_;
};

