#include "ParameterEnemy.h"

ParameterEnemy::ParameterEnemy()
{
}

ParameterEnemy::~ParameterEnemy()
{
}

void ParameterEnemy::LoadParameter(const Json& parameter)
{
	ParameterCharacter::LoadParameter(parameter);
}
