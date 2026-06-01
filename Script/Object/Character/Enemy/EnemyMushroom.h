#pragma once
#include "EnemyBase.h"
class EnemyMushroom : public EnemyBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ</param>
	explicit EnemyMushroom(std::unique_ptr<ParameterEnemy> parameter);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyMushroom() override;
};

