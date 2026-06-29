#include "ParameterGimmickBamboo.h"

ParameterGimmickBamboo::ParameterGimmickBamboo()
{
}

ParameterGimmickBamboo::~ParameterGimmickBamboo()
{
}

void ParameterGimmickBamboo::LoadParameter(const Json& parameter)
{
	ParameterGimmick::LoadParameter(parameter);
	reflectCountMax_ = parameter.value("reflectCountMax", -1);

}
