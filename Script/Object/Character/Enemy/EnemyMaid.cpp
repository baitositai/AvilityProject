#include "EnemyMaid.h"

EnemyMaid::EnemyMaid(std::unique_ptr<ParameterEnemy> parameter) :
	EnemyBase(std::move(parameter))
{
	// プレイヤー用のパラメータ
	parameterEnemyMaid_ = dynamic_cast<ParameterEnemyMaid*>(GetParameterEnemyPtr());
	assert(parameterEnemyMaid_ != nullptr);
}

EnemyMaid::~EnemyMaid()
{
}
