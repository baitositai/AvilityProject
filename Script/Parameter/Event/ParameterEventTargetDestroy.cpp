#include "ParameterEventTargetDestroy.h"

ParameterEventTargetDestroy::ParameterEventTargetDestroy() :
    targetMax_(-1),
    targetMin_(-1),
    createRangeOffset_(Vector2())
{
}

ParameterEventTargetDestroy::~ParameterEventTargetDestroy()
{
}

void ParameterEventTargetDestroy::LoadParameter(const Json& parameter)
{
    // 親クラスの共通パラメータの読み込み
    ParameterEvent::LoadParameter(parameter);

    targetMax_ = parameter.value("targetMax", -1);
    targetMin_ = parameter.value("targetMin", -1);
    targetSize_ = parameter.value("targetSize", 0.0f);
    if (parameter.contains("createRangeOffset"))
    {
        createRangeOffset_.x = parameter["createRangeOffset"].value("x", -1);
        createRangeOffset_.y = parameter["createRangeOffset"].value("y", -1);
    }
}
