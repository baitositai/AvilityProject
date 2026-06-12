#include "GimmickTarget.h"

GimmickTarget::GimmickTarget(std::unique_ptr<ParameterGimmickTarget> parameter) :
	GimmickBase(std::move(parameter))
{
	// パラメータ情報
	parameterTarget_ = dynamic_cast<ParameterGimmickTarget*>(GetParameterGimmickPtr());
	assert(parameterTarget_ != nullptr);
}

GimmickTarget::~GimmickTarget()
{
}

void GimmickTarget::Update()
{
	// 基底クラスの処理
	//ActorBase::Update();
}