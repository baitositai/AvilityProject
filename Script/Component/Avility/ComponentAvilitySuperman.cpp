#include "../../Object/Character/Player.h"
#include "ComponentAvilitySuperman.h"

ComponentAvilitySuperman::ComponentAvilitySuperman(Player& owner) :
	ComponentAvilityBase(owner)
{
	type_ = AvilityTypes::TYPE::SUPERMAN;
}

ComponentAvilitySuperman::~ComponentAvilitySuperman()
{	
}

void ComponentAvilitySuperman::Create()
{
	ComponentAvilityBase::Create();
	Init();
}

void ComponentAvilitySuperman::Init()
{	
}

void ComponentAvilitySuperman::Remove()
{
	ComponentAvilityBase::Remove();
}
