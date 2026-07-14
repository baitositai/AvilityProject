#include "ParameterGimmickTrain.h"

ParameterGimmickTrain::ParameterGimmickTrain()
{
}

ParameterGimmickTrain::~ParameterGimmickTrain()
{
}

void ParameterGimmickTrain::LoadParameter(const Json& parameter)
{
	ParameterGimmick::LoadParameter(parameter);
	ParameterActor::LoadParameterAnimation(parameter);
}