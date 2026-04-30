#include "ComponentBase.h"

ComponentBase::ComponentBase(ActorBase* owner) :
	owner_(owner)
{
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