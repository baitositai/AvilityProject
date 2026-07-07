#pragma once
#include <unordered_map>
#include "../../Manager/Game/CollisionTags.h"
#include "../../Common/IntVector3.h"
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

    /// <summary>
    /// 足の位置を返す
    /// </summary>
    /// <returns>足の位置</returns>
    const Vector2F GetFootPos();

    // アクション判定
    bool isAction_;

    // ジャンプ回数
    int jumpCount_;

    // 最大ジャンプ回数
    int jumpCountMax_;

    // 防御率
    float defenseRate_;

    // 最大無敵時間
    float invincibleTimeMax_;

    // 無敵時間
    float invincibleTime_;

    // ジャンプ力
    float jumpPow_;

    // ジャンプ力の最大量
    float jumpPowMax_;

    // 通常攻撃開始フレーム
	int defaultAttackStartFrame_;

    // 通常攻撃2回目の判定フレーム
	int defaultAttackSecondFrame_;

    // 通常攻撃の当たり判定距離
    float defaultAttackDistance_;

    // 通常攻撃の範囲半径
    float defaultAttackRadius_;

    // ダメージカラー
    VECTOR damageColor_;

    // UIダメージカラー
    IntVector3 uiDamageColor_;

    // 攻撃用の衝突タグ
	CollisionTags::TAG attackCollisionTag_;

    // 状態別コンポーネント配列
    std::unordered_map<std::string, std::string> stateComponentKeys_;
};