#pragma once
#include "EnemyBase.h"
#include "../../Parameter/Character/Enemy/ParameterEnemyMaid.h"

class EnemyMaid : public EnemyBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ</param>
	explicit EnemyMaid(std::unique_ptr<ParameterEnemyMaid> parameter);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyMaid() override;

private:

	// パラメータ情報
	ParameterEnemyMaid* parameterEnemyMaid_;
};