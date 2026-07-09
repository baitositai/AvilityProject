#include "../../Parameter/Character/Enemy/ParameterEnemyGaiaGolem.h"
#include "EnemyGaiaGolem.h"

EnemyGaiaGolem::EnemyGaiaGolem(std::unique_ptr<ParameterEnemyGaiaGolem> parameter):
	EnemyBoss(std::move(parameter))
{
	//専用のパラメータ
	parameterEnemyGaiaGolem_ = dynamic_cast<ParameterEnemyGaiaGolem*>(GetParameterEnemyBossPtr());
	assert(parameterEnemyGaiaGolem_ != nullptr);
}

EnemyGaiaGolem::~EnemyGaiaGolem()
{
}
