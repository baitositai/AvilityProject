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
    ParameterCharacter::LoadParameter(parameter);

    // 敵固有パラメータの読み込み
    animationsIdle_ = parameter.value("animationsIdle", -1);
    animationsWalk_ = parameter.value("animationsWalk", -1);
    animationsBrake_ = parameter.value("animationsBrake", -1);
    animationsAttack_ = parameter.value("animationsAttack", -1);
    animationsJump_ = parameter.value("animationsJump", -1);
    animationsFall_ = parameter.value("animationsFall", -1);
    animationsDie_ = parameter.value("animationsDie", -1);
    animationsDamage_ = parameter.value("animationsDamage", -1);
    animationsPause_ = parameter.value("animationsPause", -1);
    animationAttackSpeed_ = parameter.value("animationAttackSpeed", 0.0f);
}