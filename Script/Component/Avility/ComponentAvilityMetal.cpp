#include "../../Object/Character/Player.h"
#include "ComponentAvilityMetal.h"

ComponentAvilityMetal::ComponentAvilityMetal(Player& owner) :
	ComponentAvilityBase(owner)
{
	type_ = AvilityTypes::TYPE::METAL;
}

ComponentAvilityMetal::~ComponentAvilityMetal()
{
}

void ComponentAvilityMetal::Create()
{
	ComponentAvilityBase::Create();
	Init();
}

void ComponentAvilityMetal::Init()
{
}

void ComponentAvilityMetal::Remove()
{
	ComponentAvilityBase::Remove();
}