#include "EnemyAzagrim.h"

EnemyAzagrim::EnemyAzagrim(std::unique_ptr<ParameterEnemyAzagrim> parameter) :
	EnemyBoss(std::move(parameter))
{
	//専用のパラメータ
	parameterEnemyAzagrim_ = dynamic_cast<ParameterEnemyAzagrim*>(GetParameterEnemyBossPtr());
	assert(parameterEnemyAzagrim_ != nullptr);
}

EnemyAzagrim::~EnemyAzagrim()
{
}

void EnemyAzagrim::Update()
{
	EnemyBoss::Update();
}