#include "EnemyMaid.h"

EnemyMaid::EnemyMaid(std::unique_ptr<ParameterEnemyMaid> parameter) :
	EnemyBoss(std::move(parameter))
{
	// 専用のパラメータ
	parameterEnemyMaid_ = dynamic_cast<ParameterEnemyMaid*>(GetParameterEnemyBossPtr());
	assert(parameterEnemyMaid_ != nullptr);
}

EnemyMaid::~EnemyMaid()
{
}
