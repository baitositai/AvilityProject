#pragma once
#include "EnemyBase.h"

class EnemyMaid : public EnemyBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ</param>
	explicit EnemyMaid(std::unique_ptr<ParameterEnemy> parameter);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyMaid() override;

private:

};