#include "ParameterEnemyMaid.h"

ParameterEnemyMaid::ParameterEnemyMaid() :
	hitFoodCount_(0),
	triggerFoodCount_(0)
{
}

ParameterEnemyMaid::~ParameterEnemyMaid()
{
}

void ParameterEnemyMaid::LoadParameter(const Json& parameter)
{
	// Šî’êƒNƒ‰ƒX‚Ì“Ç‚İ‚İ
	ParameterEnemyBoss::LoadParameter(parameter);
	triggerFoodCount_ = parameter.value("triggerFoodCount", -1);
}
