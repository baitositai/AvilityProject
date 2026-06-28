#include "ParameterGimmickTarget.h"

ParameterGimmickTarget::ParameterGimmickTarget() :
	isMove_(false),
	moveLimit_({})
{
}

ParameterGimmickTarget::~ParameterGimmickTarget()
{
}

void ParameterGimmickTarget::LoadParameter(const Json& parameter)
{
	ParameterGimmick::LoadParameter(parameter);
}
