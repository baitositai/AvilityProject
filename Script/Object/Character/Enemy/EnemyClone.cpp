#include <DxLib.h>
#include "../../Common/Animation.h"
#include "EnemyClone.h"

EnemyClone::EnemyClone(std::unique_ptr<ParameterEnemyClone> parameter) :
	EnemyBase(std::move(parameter))
{
	// プレイヤー用のパラメータ
	parameterEnemy_ = dynamic_cast<ParameterEnemyClone*>(GetParameterEnemyPtr());
	assert(parameterEnemy_ != nullptr);
}

EnemyClone::~EnemyClone()
{
}