#pragma once
#include "UiPlayerBase.h"
#include "../../Common/CharacterString.h"
#include "../../Component/Avility/AvilityTypes.h"

class UiPlayerGetItemMessage :
    public UiPlayerBase
{
public:

    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="owner">所有者</param>
    UiPlayerGetItemMessage(const Player& owner);

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
    /// アビリティの取得メッセージを追加
    /// </summary>
    /// <param name="getAvilitytype"></param>
    void AddAvilityMessage(const AvilityTypes::TYPE& getAvilitytype);
private:

    //アビリティ取得時の共通文字列　
    const std::wstring GET_AVILITY_MESSAGE_COMMON = L"を取得！";

    //アビリティの文字列マップ
    std::unordered_map<AvilityTypes::TYPE, std::wstring>abilityStr_;

    //描画する文字列
    CharacterString characterString_;

    //表示時間
    float drawCnt_;
};

