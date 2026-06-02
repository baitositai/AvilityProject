#include "ParameterEnemyClone.h"

ParameterEnemyClone::ParameterEnemyClone() :
    animationsIdle_(-1),
    animationsWalk_(-1),
    animationsBrake_(-1),
    animationsAttack_(-1),
    animationsJump_(-1),
    animationsFall_(-1),
    animationsDie_(-1),
    animationsDamage_(-1),
    animationsPause_(-1),
    animationAttackSpeed_(0.0f)
{
}

ParameterEnemyClone::~ParameterEnemyClone()
{
}

void ParameterEnemyClone::LoadParameter(const Json& parameter)
{
    // 親クラスであるキャラクター共通パラメータの読み込み
    ParameterEnemy::LoadParameter(parameter);
}