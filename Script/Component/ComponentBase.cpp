#include "ComponentBase.h"

ComponentBase::ComponentBase(ActorBase* owner) :
	owner_(owner)
{
	isActive_ = true;
}

ComponentBase::~ComponentBase()
{
}

void ComponentBase::Init()
{
}

void ComponentBase::Update()
{
}