#include "../../System/Event/EventBase.h"
#include "UiEventBase.h"

UiEventBase::UiEventBase(const EventBase& event) :
	eventBase_(event)
{
}

UiEventBase::~UiEventBase()
{
}

void UiEventBase::Update()
{
	if (eventBase_.IsDelete())
	{
		Delete();
	}
}