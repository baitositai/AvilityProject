#pragma once
#include <unordered_map>
#include <functional>
#include "UiPlayerBase.h"
#include "../../Parameter/Character/Player/ParameterPlayer.h"

class UiPlayerNum : public UiPlayerBase
{
public:

    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="owner">所有者</param>
    UiPlayerNum(const Player& owner);

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~UiPlayerNum() override;

    /// <summary>
    /// 初期化
    /// </summary>
    void Init() override;

    /// <summary>
    /// 更新
    /// </summary>
    void Update() override;

    /// <summary>
    /// 描画処理
    /// </summary>
    void Draw() override;

private:

    //ローカル座標
    static constexpr float DRAW_LOCAL_POS_Y = -60.0f;

    // 前のUI種類
    ParameterPlayer::HEAD_UI preUiType_;

    // UI変更用マップ
    std::unordered_map < ParameterPlayer::HEAD_UI, std::function<void()>> uiChangeMap_;

    // リソースの変更
    void ChangeResourceUi(const ParameterPlayer::HEAD_UI headUiType);
    void ChangeResourceUiPadNo();
    void ChangeResourceUiGetItem();
    void ChangeResourceUiEnter();
    void ChangeResourceUiOpen();
};

