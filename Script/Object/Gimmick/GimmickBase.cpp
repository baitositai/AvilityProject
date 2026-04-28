#include "../Common/Animation.h"
#include "GimmickBase.h"

GimmickBase::GimmickBase(Parameter* parameter, const std::vector<std::string>& componentNameList):
	ActorBase(parameter,componentNameList)
{
}

GimmickBase::~GimmickBase()
{
}

void GimmickBase::Init(void)
{
	ActorBase::Init();
}

void GimmickBase::Update(void)
{
	ActorBase::Update();
}

void GimmickBase::Draw(void)
{
	//ActorBase::Draw();
}

void GimmickBase::DebugDraw(void)
{
	ActorBase::DebugDraw();
}
