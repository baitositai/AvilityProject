#include "ParameterPlayer.h"

ParameterPlayer::ParameterPlayer() :
    shotVec_({ 0.0f, 0.0f }),
    dashSpeed_(0.0f),
    padNo_(Input::JOYPAD_NO::PAD1),
    isHitItem_(false)
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

    // ショットベクトルの読み込み
    if (parameter.contains("shotVec"))
    {
        shotVec_.x = parameter["shotVec"].value("x", 0.0f);
        shotVec_.y = parameter["shotVec"].value("y", 0.0f);
    }
}