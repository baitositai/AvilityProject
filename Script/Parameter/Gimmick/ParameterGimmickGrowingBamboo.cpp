#include "ParameterGimmickGrowingBamboo.h"

ParameterGimmickGrowingBamboo::ParameterGimmickGrowingBamboo()
{
}

ParameterGimmickGrowingBamboo::~ParameterGimmickGrowingBamboo()
{
}

void ParameterGimmickGrowingBamboo::LoadParameter(const Json& parameter)
{
	ParameterGimmick::LoadParameter(parameter);
	growCountMax_ = parameter.value("growCountMax", -1);    
	deleteWaitTime_ = parameter.value("deleteWaitTime", 0.0f);
	growIntervalTime_ = parameter.value("growingInterval", 0.0f);
}
