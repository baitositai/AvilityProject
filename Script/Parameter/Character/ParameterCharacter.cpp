#include "ParameterCharacter.h"

ParameterCharacter::ParameterCharacter() :
    isAction_(false),
    jumpCount_(-1),
    jumpCountMax_(-1),
    defaultAttackStartFrame_(-1),
    defenseRate_(0.0f),
    invincibleTimeMax_(0.0f),
    invincibleTime_(0.0f),
    jumpPow_(0.0f),
    jumpPowMax_(0.0f),
    defaultAttackDistance_(0.0f),
    defaultAttackRadius_(0.0f),
    damageColor_({}),
    attackCollisionTag_(CollisionTags::TAG::NONE)
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
    jumpCount_ = parameter.value("jumpCount", -1);
    jumpCountMax_ = parameter.value("jumpCountMax", -1);
    attackBoostRate_ = parameter.value("attackBoostRate", 0.0f);
    defenseRate_ = parameter.value("damageRate", 0.0f);
    invincibleTimeMax_ = parameter.value("invincibleTimeMax", 0.0f);
    invincibleTime_ = parameter.value("invincibleTime", 0.0f);
    jumpPow_ = parameter.value("jumpPow", 0.0f);
    jumpPowMax_ = parameter.value("jumpPowerMax", 0.0f);
    defaultAttackRadius_ = parameter.value("defaultAttackRadius", 0.0f);
    defaultAttackDistance_ = parameter.value("defaultAttackDistance", 0.0f);
    defaultAttackStartFrame_ = parameter.value("defaultAttackStartFrame", -1);
    stateComponentKeys_ = parameter.value("stateComponentKeys", std::unordered_map<std::string, std::string>());

    // ノックバックパワーの読み込み
    if (parameter.contains("knockBackPower"))
    {
        knockBackPower_.x = parameter["knockBackPower"].value("x", 0.0f);
        knockBackPower_.y = parameter["knockBackPower"].value("y", 0.0f);
    }

    if (parameter.contains("damageColor"))
    {
        damageColor_.x = parameter["damageColor"].value("r", 0);
        damageColor_.y = parameter["damageColor"].value("g", 0);
        damageColor_.z = parameter["damageColor"].value("b", 0);
    }

    // アニメーションデータの取得
    LoadParameterAnimation(parameter);
}