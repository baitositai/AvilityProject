#include "EnemySamurai.h"

EnemySamurai::EnemySamurai(std::unique_ptr<ParameterEnemy> parameter) :
	EnemyBase(std::move(parameter))
{
}

EnemySamurai::~EnemySamurai()
{
}
