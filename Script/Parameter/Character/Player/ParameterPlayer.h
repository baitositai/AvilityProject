#pragma once
#include "../ParameterCharacter.h"
#include "../../Manager/Common/Input.h"
#include "../../Manager/Game/ItemTypes.h"

class ParameterPlayer : public ParameterCharacter
{
public:
    
    struct TreasureStatus
    {
        ItemTypes::TREASURE_TYPE type;
        int amount;
        Vector2 size;
    };

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

    // アイテムとの衝突判定
    bool isHitItem_;

    // 保持しているお宝情報
    std::vector<TreasureStatus> treasureList_;

    // 入力パッド
    Input::JOYPAD_NO padNo_;
};

