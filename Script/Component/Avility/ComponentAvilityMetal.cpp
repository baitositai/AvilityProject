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
	VECTOR outlineColor = owner_.GetOutlineColor();

	owner_.SetMaterialBuf(2, FLOAT4{ outlineColor.x,
		outlineColor.y,
		outlineColor.z,
		1.0f });
}

void ComponentAvilityMetal::Remove()
{
	VECTOR outlineColor = owner_.GetOutlineColor();

	owner_.SetMaterialBuf(2, FLOAT4{ outlineColor.x,
		outlineColor.y,
		outlineColor.z,
		0.0f });

	ComponentAvilityBase::Remove();
}