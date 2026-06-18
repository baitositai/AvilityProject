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

    // アビリティのパラメータを取得
    LoadAvilityBoostParameter(parameter);
}

void ParameterPlayer::SetAvilityBoost(const AvilityTypes::TYPE type)
{
    const AvilityBoostStatus& status = avilityBoostStatusMap_.at(type);

    // 設定
    attackBoostRate_ += status.attackBoostRate;
    moveSpeedBoostRate_ += status.moveSpeedBoostRate;
    gravityBoostRate_ += status.gravityBoostRate;
    defenseRate_ += status.defenceRate;
}

void ParameterPlayer::RemoveAvilityBoost(const AvilityTypes::TYPE type)
{
    const AvilityBoostStatus& status = avilityBoostStatusMap_.at(type);

    // 解除
    attackBoostRate_ -= status.attackBoostRate;
    moveSpeedBoostRate_ -= status.moveSpeedBoostRate;
    gravityBoostRate_ -= status.gravityBoostRate;
    defenseRate_ -= status.defenceRate;
}

void ParameterPlayer::LoadAvilityBoostParameter(const Json& parameter)
{
    const auto& avilityData = parameter["avility"];
    for (int i = 0; i < AvilityTypes::AVILITY_TYPE_MAX; i++)
    {
        // 構造体生成
        AvilityBoostStatus status = {};

        // 格納する種類を取得
        AvilityTypes::TYPE type = static_cast<AvilityTypes::TYPE>(i);
        std::string stringType = AvilityTypes::AVILITY_NAME_MAP.at(type);

        // 値の設定
        const auto& avilityParameter = avilityData[stringType];
        status.attackBoostRate = avilityParameter.value("attackBoostRate", 0.0f);
        status.moveSpeedBoostRate = avilityParameter.value("moveSpeedBoostRate", 0.0f);
        status.gravityBoostRate = avilityParameter.value("gravityBoostRate", 0.0f);
        status.defenceRate = avilityParameter.value("defenceRate", 0.0f);

        // 格納
        avilityBoostStatusMap_.emplace(type, status);
    }
}