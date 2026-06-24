#pragma once
#include "../ParameterCharacter.h"
#include "../../Manager/Common/Input.h"
#include "../../Manager/Game/ItemTypes.h"
#include "../../Component/Avility/AvilityTypes.h"

class ParameterPlayer : public ParameterCharacter
{
public:
    
    struct TreasureStatus
    {
        ItemTypes::TREASURE_TYPE type = ItemTypes::TREASURE_TYPE::MAX;
        int amount = -1;
        Vector2 size = {};
    };

    struct AvilityBoostStatus
    {
        float attackBoostRate = 0.0f;
        float moveSpeedBoostRate = 0.0f;
        float gravityBoostRate = 0.0f;
        float defenceRate = 0.0f;
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
    
    /// <summary>
    /// アビリティバフの設定
    /// </summary>
    /// <param name="type">種類</param>
    void SetAvilityBoost(const AvilityTypes::TYPE type);

    /// <summary>
    /// アビリティバフを解除
    /// </summary>
    /// <param name="type">種類</param>
    void RemoveAvilityBoost(const AvilityTypes::TYPE type);

    // ショットベクトル
    Vector2F shotVec_;

    // ダッシュスピード
    float dashSpeed_;

    // 選択時間
    float selectAvilityTime_;

    // アイテムとの衝突判定
    bool isHitItem_;

    // 保持しているお宝情報
    std::vector<TreasureStatus> treasureList_;

    // 入力パッド
    Input::JOYPAD_NO padNo_;

    // アビリティの能力マップ
    std::unordered_map<AvilityTypes::TYPE, AvilityBoostStatus> avilityBoostStatusMap_;    
    
private:

    // アビリティのバフの読み込み
    void LoadAvilityBoostParameter(const Json& parameter);
};

