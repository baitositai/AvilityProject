#include "EnemySnake.h"

EnemySnake::EnemySnake(std::unique_ptr<ParameterEnemy> parameter) : 
	EnemyBase(std::move(parameter))
{
}

EnemySnake::~EnemySnake()
{
}