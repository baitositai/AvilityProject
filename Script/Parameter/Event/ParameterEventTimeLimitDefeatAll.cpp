#include "ParameterEventTimeLimitDefeatAll.h"

ParameterEventTimeLimitDefeatAll::ParameterEventTimeLimitDefeatAll() :
    waveMax_(-1),
    waveMin_(-1),
    enemyNumMax_(-1),
    enemyNumMin_(-1),
    createRange_(Vector2()),
    createLeftTopPos_(Vector2())
{
}

ParameterEventTimeLimitDefeatAll::~ParameterEventTimeLimitDefeatAll()
{
}

void ParameterEventTimeLimitDefeatAll::LoadParameter(const Json& parameter)
{
    waveMax_ = parameter.value("waveMax", -1);
    waveMin_ = parameter.value("waveMin", -1);
    enemyNumMax_ = parameter.value("enemyNumMax", -1);
    enemyNumMin_ = parameter.value("enemyNumMin", -1);

    if (parameter.contains("createRange"))
    {
        createRange_.x = parameter["createRange"].value("x", -1);
        createRange_.y = parameter["createRange"].value("y", -1);
    }
    if (parameter.contains("createLeftTopPos"))
    {
        createLeftTopPos_.x = parameter["createLeftTopPos"].value("x", -1);
        createLeftTopPos_.y = parameter["createLeftTopPos"].value("y", -1);
    }
}