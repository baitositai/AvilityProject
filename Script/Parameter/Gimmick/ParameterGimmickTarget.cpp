#include "ParameterGimmickTarget.h"

ParameterGimmickTarget::ParameterGimmickTarget() :
	isMove_(false),
	moveDir_({}),
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
