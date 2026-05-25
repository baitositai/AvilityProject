#pragma once
#include "../ParameterCharacter.h"

class ParameterPlayer : public ParameterCharacter
{
public:

    /// <summary>
    /// コンストラクタ
    /// </summary>
    ParameterPlayer();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~ParameterPlayer() override;

    /// <summary>
    /// 外部データの読み込み
    /// </summary>
    /// <param name="parameter">読み込むJSONデータ</param>
    void LoadParameter(const Json& parameter) override;

    // ショットベクトル
    Vector2F shotVec_;

    // ダッシュスピード
    float dashSpeed_;

    // 待機アニメーション数
    int animationsIdle_;

    // 移動アニメーション
    int animationsWalk_;

    // ブレーキアニメーション
    int animationsBrake_;

    // 攻撃アニメーション
    int animationsAttack_;

    // ジャンプアニメーション
    int animationsJump_;

    // 落下アニメーション
    int animationsFall_;

    // 死亡アニメーション
    int animationsDie_;

    // ダメージアニメーション
    int animationsDamage_;

    // ポーズアニメーション
    int animationsPause_;

    // 攻撃アニメーション速度
    float animationAttackSpeed_;
};

