#include "EnemyMushroom.h"

EnemyMushroom::EnemyMushroom(std::unique_ptr<ParameterEnemy> parameter) :
	EnemyBase(std::move(parameter))
{
}

EnemyMushroom::~EnemyMushroom()
{
}
