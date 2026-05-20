#include "../Common/Animation.h"
#include "GimmickBase.h"

GimmickBase::GimmickBase(std::unique_ptr<ParameterGimmick> parameter) :
	ActorBase(std::move(parameter))
{
	// ÉpÉâÉÅÅ[É^
	parameterGimmick_ = dynamic_cast<ParameterGimmick*>(GetParameterGimmickPtr());
	assert(parameterGimmick_ != nullptr);
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
