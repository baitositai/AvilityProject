#include "ParameterGimmick.h"

ParameterGimmick::ParameterGimmick()
{
}

ParameterGimmick::~ParameterGimmick()
{
}

void ParameterGimmick::LoadParameter(const Json& parameter)
{
	ParameterActor::LoadParameter(parameter);
}
