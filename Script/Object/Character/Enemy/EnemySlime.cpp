#include "EnemySlime.h"

EnemySlime::EnemySlime(std::unique_ptr<ParameterEnemy> parameter) :
	EnemyBase(std::move(parameter))
{
	parameterEnemySlime_ = GetParameterEnemyPtr();
}

EnemySlime::~EnemySlime()
{
}
