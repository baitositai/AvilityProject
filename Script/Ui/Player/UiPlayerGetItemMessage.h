#pragma once
#include "UiPlayerBase.h"
#include "../../Common/CharacterString.h"
#include "../../Component/Avility/AvilityTypes.h"

class UiPlayerGetItemMessage :
    public UiPlayerBase
{
public:

    // メッセージ種類
    enum class TYPE
    {
        ABILITY,
        ATTACK_UP,
        LIFE_UP,
        SPEED_UP,
        MAX
    };

    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="owner">所有者</param>
    /// <param name="type">種類</param>
    UiPlayerGetItemMessage(const Player& owner, const TYPE type);

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~UiPlayerGetItemMessage() override;

    /// <summary>
    /// 初期化
    /// </summary>
    void Init() override;

    /// <summary>
    /// 更新
    /// </summary>
    void Update() override;

    /// <summary>
    /// 描画
    /// </summary>
    void Draw() override;

    /// <summary>
    /// アビリティ種類の設定
    /// </summary>
    /// <param name="type">アビリティ種類</param>
    void SetAbilityType(const AvilityTypes::TYPE type) { abilityType_ = type; }

    /// <summary>
    /// パワーの設定
    /// </summary>
    /// <param name="power">上昇値</param>
    void SetPower(const int power) { power_ = power; }

private:

    //アビリティ取得時の共通文字列　
    const std::wstring GET_AVILITY_MESSAGE_COMMON = L"を取得！";

    // 移動速度
    static constexpr float MOVE_SPEED = 0.08f;

    // α値変更速度
    static constexpr float ALPHA_SPEED = 5.0f;

    // 削除時間
    static constexpr float DELETE_TIME = 2.0f;

    // 種類
    TYPE type_;

    // アビリティ種類
    AvilityTypes::TYPE abilityType_;

    // パワー値
    int power_;

    //アビリティの文字列マップ
    std::unordered_map<AvilityTypes::TYPE, std::wstring>abilityStr_;

    //描画する文字列
    CharacterString characterString_;

    // 透過値
    float alpha_;
};

