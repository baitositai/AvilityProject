#pragma once
#include "UiPlayerBase.h"
class UiPlayerNum :
    public UiPlayerBase
{
public:

    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="_owner">所有者</param>
    UiPlayerNum(const Player& _owner);

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

private:

    //ローカル座標
    static constexpr float DRAW_LOCAL_POS_Y = -60.0f;

    //描画色
    int red_;
    int green_;
    int blue_;
};

