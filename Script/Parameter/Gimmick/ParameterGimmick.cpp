#include "ParameterGimmick.h"

ParameterGimmick::ParameterGimmick() :
	moveDir_({})
{
}

ParameterGimmick::~ParameterGimmick()
{
}

void ParameterGimmick::LoadParameter(const Json& parameter)
{
	ParameterActor::LoadParameter(parameter);
}
