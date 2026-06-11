#include "EventTargetDestroy.h"

EventTargetDestroy::EventTargetDestroy(std::unique_ptr<ParameterEventTargetDestroy> parameter) :
	EventBase(std::move(parameter))
{
}

EventTargetDestroy::~EventTargetDestroy()
{
}
