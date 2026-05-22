#include "../Common/Animation.h"
#include "GimmickBase.h"

GimmickBase::GimmickBase(std::unique_ptr<ParameterActor> parameter) :
	ActorBase(std::move(parameter))
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
	ActorBase::Draw();
}

void GimmickBase::DebugDraw(void)
{
	ActorBase::DebugDraw();
}
