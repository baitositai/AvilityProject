#pragma once
#include <unordered_map>
#include "../ParameterActor.h"

class ParameterCharacter : public ParameterActor
{
public:

    /// <summary>
    /// コンストラクタ
    /// </summary>
    ParameterCharacter();

    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~ParameterCharacter();

    /// <summary>
    /// 外部データの読み込み
    /// </summary>
    /// <param name="parameter">読み込むJSONデータ</param>
    virtual void LoadParameter(const Json& parameter) override;

    // 体力
    int hp_;

    // 攻撃力
    int attackPower_;

    // ジャンプ回数
    int jumpCount_;

    // 最大ジャンプ回数
    int jumpCountMax_;

    // 攻撃力上昇率
    float attackBoostRate_;

    // 防御率
    float damageRate_;

    // 最大無敵時間
    float invincibleTimeMax_;

    // 無敵時間
    float invincibleTime_;

    // ジャンプ力
    float jumpPow_;

    // ジャンプ力の最大量
    float jumpPowMax_;

    // ノックバックパワー
    Vector2F knockBackPower_;

    // ノックバック距離
    float knockBackDistance_;

    // 通常攻撃の当たり判定調整座標
    Vector2F defaultAttackLocalPos_;

    // 通常攻撃の範囲半径
    float defaultAttackRadius_;

    // 状態別コンポーネント配列
    std::unordered_map<std::string, std::string> stateComponentKeys_;
};