#include "ParameterEvent.h"

ParameterEvent::ParameterEvent() : 
	challengeTime_(0.0f),
	endTime_(0.0f)
{
}

ParameterEvent::~ParameterEvent()
{
}

void ParameterEvent::LoadParameter(const Json& parameter)
{
	challengeTime_ = parameter.value("challengeTime", 0.0f);
	endTime_ = parameter.value("endTime", 0.0f);
}