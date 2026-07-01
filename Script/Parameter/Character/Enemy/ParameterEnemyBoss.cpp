#include "ParameterEnemyBoss.h"

ParameterEnemyBoss::ParameterEnemyBoss()
{
}

ParameterEnemyBoss::~ParameterEnemyBoss()
{
}

void ParameterEnemyBoss::LoadParameter(const Json& parameter)
{
	ParameterEnemy::LoadParameter(parameter);
	bossUiNamePlateIndex_ = parameter.value("bossUiNamePlateIndex",-1);
}
