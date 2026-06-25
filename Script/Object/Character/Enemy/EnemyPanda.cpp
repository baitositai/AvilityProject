#include "EnemyPanda.h"

EnemyPanda::EnemyPanda(std::unique_ptr<ParameterEnemyPanda> parameter) :
	EnemyBase(std::move(parameter))
{
	// 専用のパラメータ
	parameterEnemyPanda_ = dynamic_cast<ParameterEnemyPanda*>(GetParameterEnemyPtr());
	assert(parameterEnemyPanda_ != nullptr);
}

EnemyPanda::~EnemyPanda()
{
}