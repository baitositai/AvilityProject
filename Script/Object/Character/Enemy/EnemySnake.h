#pragma once
#include "EnemyBase.h"

class EnemySnake : public EnemyBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ</param>
	explicit EnemySnake(std::unique_ptr<ParameterEnemy> parameter);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemySnake() override;

};