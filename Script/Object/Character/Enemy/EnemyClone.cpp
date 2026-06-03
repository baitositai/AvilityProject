#include <DxLib.h>
#include "../../Common/Animation.h"
#include "EnemyClone.h"

EnemyClone::EnemyClone(std::unique_ptr<ParameterEnemy> parameter) :
	EnemyBase(std::move(parameter))
{
	// クローン用のパラメータ
	parameterEnemyClone_ = GetParameterEnemyPtr();
}

EnemyClone::~EnemyClone()
{
}