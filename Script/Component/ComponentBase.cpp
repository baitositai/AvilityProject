#include "ComponentBase.h"

ComponentBase::ComponentBase(ActorBase* owner) :
	owner_(owner)
{
}

ComponentBase::~ComponentBase()
{
}

void ComponentBase::Update()
{
}