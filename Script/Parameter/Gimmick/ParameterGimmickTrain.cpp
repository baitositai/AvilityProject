#include "ParameterGimmickTrain.h"

ParameterGimmickTrain::ParameterGimmickTrain()
{
	waitTimeMax_ = 0.0f;
	waitTimeMin_ = 0.0f;
}

ParameterGimmickTrain::~ParameterGimmickTrain()
{
}

void ParameterGimmickTrain::LoadParameter(const Json& parameter)
{
	ParameterGimmick::LoadParameter(parameter);
	ParameterActor::LoadParameterAnimation(parameter);
	waitTimeMax_ = parameter.value("waitTimeMax", 0.0f);
	waitTimeMin_ = parameter.value("waitTimeMin", 0.0f);
}