#include "EnemyHat.h"

EnemyHat::EnemyHat(std::unique_ptr<ParameterEnemy> parameter) :
	EnemyBase(std::move(parameter))
{
}

EnemyHat::~EnemyHat()
{
}