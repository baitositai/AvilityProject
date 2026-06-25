#include "EnemyMaid.h"

EnemyMaid::EnemyMaid(std::unique_ptr<ParameterEnemyMaid> parameter) :
	EnemyBase(std::move(parameter))
{
	// 専用のパラメータ
	parameterEnemyMaid_ = dynamic_cast<ParameterEnemyMaid*>(GetParameterEnemyPtr());
	assert(parameterEnemyMaid_ != nullptr);
}

EnemyMaid::~EnemyMaid()
{
}
