#include "ParameterPlayer.h"

ParameterPlayer::ParameterPlayer() :
    shotVec_({ 0.0f, 0.0f }),
    dashSpeed_(0.0f),
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

ParameterPlayer::~ParameterPlayer()
{
}

void ParameterPlayer::LoadParameter(const Json& parameter)
{
    // 親クラスであるキャラクター共通パラメータの読み込み
    ParameterCharacter::LoadParameter(parameter);

    // プレイヤー固有パラメータの読み込み
    dashSpeed_ = parameter.value("dashSpeed", 0.0f);
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

    // ショットベクトルの読み込み
    if (parameter.contains("shotVec"))
    {
        shotVec_.x = parameter["shotVec"].value("x", 0.0f);
        shotVec_.y = parameter["shotVec"].value("y", 0.0f);
    }
}