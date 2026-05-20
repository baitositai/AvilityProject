#include "ParameterCharacter.h"

ParameterCharacter::ParameterCharacter() :
    hp_(-1),
    attackPower_(-1),
    jumpCount_(-1),
    jumpCountMax_(-1),
    attackBoostRate_(0.0f),
    damageRate_(0.0f),
    invincibleTimeMax_(0.0f),
    invincibleTime_(0.0f),
    jumpPow_(0.0f),
    jumpPowMax_(0.0f),
    knockBackPower_({ 0.0f, 0.0f }),
    knockBackDistance_(0.0f),
    defaultAttackLocalPos_({ 0.0f, 0.0f }),
    defaultAttackRadius_(0.0f)
{
}

ParameterCharacter::~ParameterCharacter()
{
}

void ParameterCharacter::LoadParameter(const Json& parameter)
{
    // 親クラスであるアクター共通パラメータの読み込み
    ParameterActor::LoadParameter(parameter);

    // キャラクター固有パラメータの読み込み
    hp_ = parameter.value("hp", -1);
    attackPower_ = parameter.value("attackPower", -1);
    jumpCount_ = parameter.value("jumpCount", -1);
    jumpCountMax_ = parameter.value("jumpCountMax", -1);
    attackBoostRate_ = parameter.value("attackBoostRate", 0.0f);
    damageRate_ = parameter.value("damageRate", 0.0f);
    invincibleTimeMax_ = parameter.value("invincibleTimeMax", 0.0f);
    invincibleTime_ = parameter.value("invincibleTime", 0.0f);
    jumpPow_ = parameter.value("jumpPow", 0.0f);
    jumpPowMax_ = parameter.value("jumpPowerMax", 0.0f);
    knockBackDistance_ = parameter.value("knockBackDistance", 0.0f);
    defaultAttackRadius_ = parameter.value("defaultAttackRadius", 0.0f);
    stateComponentKeys_ = parameter.value("stateComponentKeys", std::unordered_map<std::string, std::string>());

    // ノックバックパワーの読み込み
    if (parameter.contains("knockBackPower"))
    {
        knockBackPower_.x = parameter["knockBackPower"].value("x", 0.0f);
        knockBackPower_.y = parameter["knockBackPower"].value("y", 0.0f);
    }

    // 通常攻撃の当たり判定調整座標の読み込み
    if (parameter.contains("defaultAttackLocalPos"))
    {
        defaultAttackLocalPos_.x = parameter["defaultAttackLocalPos"].value("x", 0.0f);
        defaultAttackLocalPos_.y = parameter["defaultAttackLocalPos"].value("y", 0.0f);
    }

    // アニメーションデータの取得
    LoadParameterAnimation(parameter);
}
