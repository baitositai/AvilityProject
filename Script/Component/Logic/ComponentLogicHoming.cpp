#include "../../Object/Character/Enemy/EnemyAzagrim.h"
#include "ComponentLogicHoming.h"

ComponentLogicHoming::ComponentLogicHoming(EnemyAzagrim& owner):
	ComponentLogicBase(owner),
	owner_(owner)
{
}

ComponentLogicHoming::~ComponentLogicHoming()
{
}

void ComponentLogicHoming::Create()
{
}

void ComponentLogicHoming::Init()
{
	ComponentLogicBase::Init();
}

void ComponentLogicHoming::Update()
{
	owner_.MobiusLoop();
}
