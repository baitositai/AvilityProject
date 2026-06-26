#include "GimmickBamboo.h"

GimmickBamboo::GimmickBamboo(std::unique_ptr<ParameterGimmickBamboo> parameter) :
	GimmickBase(std::move(parameter))
{
	// ƒpƒ‰ƒ[ƒ^î•ñ
	parameterBamboo_ = dynamic_cast<ParameterGimmickBamboo*>(GetParameterGimmickPtr());
	assert(parameterBamboo_ != nullptr);
}

GimmickBamboo::~GimmickBamboo()
{
}

void GimmickBamboo::Init()
{
}

void GimmickBamboo::Update()
{
}
