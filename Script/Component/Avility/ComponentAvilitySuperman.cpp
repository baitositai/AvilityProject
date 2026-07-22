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
	owner_.SetMaterialBuf(3, FLOAT4{ 1.0f,0.0f,0.0f,0.0f });
	owner_.GetAnimation().SetAnimationSpeed("attack", 0.4);
}

void ComponentAvilitySuperman::Remove()
{
	owner_.SetMaterialBuf(3, FLOAT4{ 0.0f,0.0f,0.0f,0.0f });
	owner_.GetAnimation().SetAnimationSpeed("attack", 0.2);

	ComponentAvilityBase::Remove();
}
