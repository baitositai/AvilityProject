#include "../../Object/Character/Player.h"
#include "ComponentAvilityBase.h"

ComponentAvilityBase::ComponentAvilityBase(Player& owner) :
	owner_(owner),
	ComponentBase(&owner)
{
}

ComponentAvilityBase::~ComponentAvilityBase()
{
}

void ComponentAvilityBase::Update()
{
}
