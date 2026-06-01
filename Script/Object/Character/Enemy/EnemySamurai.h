#pragma once
#include "EnemyBase.h"

class EnemySamurai : public EnemyBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter"></param>
	EnemySamurai(std::unique_ptr<ParameterEnemy> parameter);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemySamurai() override;

private:

};