#include "ParameterEnemyPanda.h"

ParameterEnemyPanda::ParameterEnemyPanda()
{
}

ParameterEnemyPanda::~ParameterEnemyPanda()
{
}

void ParameterEnemyPanda::LoadParameter(const Json& parameter)
{
	// Šî’êƒNƒ‰ƒX‚Ì“Ç‚İ‚İ
	ParameterEnemy::LoadParameter(parameter);

	// “Á•Ê‚È’l‚Ì“Ç‚İ‚İ
	defaultAttackStartFrame2_ = parameter.value("defaultAttackStartFrame2", -1);
	defaultAttackStartFrame3_ = parameter.value("defaultAttackStartFrame3", -1);
	defaultAttackStartFrame4_ = parameter.value("defaultAttackStartFrame4", -1);
}