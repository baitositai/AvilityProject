#pragma once
#include "ParameterGimmick.h"
class ParameterGimmickGroundRock :
    public ParameterGimmick
{
public:

    /// <summary>
    /// コンストラクタ
    /// </summary>
    ParameterGimmickGroundRock();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~ParameterGimmickGroundRock();

    ///// <summary>
    ///// パラメーターのロード
    ///// </summary>
    //void LoadParameter(const Json& parameter) override;

    //水平速度
    float horizonSpd_;
};

