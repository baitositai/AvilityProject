#include "EventTargetDestroy.h"

EventTargetDestroy::EventTargetDestroy(std::unique_ptr<ParameterEventTargetDestroy> parameter) :
	EventBase(std::move(parameter))
{
}

EventTargetDestroy::~EventTargetDestroy()
{
}

void EventTargetDestroy::CreateTargets()
{
}

void EventTargetDestroy::UpdateChallenge()
{
}

void EventTargetDestroy::UpdateEnd()
{
}

void EventTargetDestroy::ChangeStateChallenge()
{
}

void EventTargetDestroy::ChangeStateEnd()
{
}
