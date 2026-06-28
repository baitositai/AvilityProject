#include "GimmickGrowingBamboo.h"

GimmickGrowingBamboo::GimmickGrowingBamboo(std::unique_ptr<ParameterGimmickGrowingBamboo> parameter) :
	GimmickBase(std::move(parameter))
{
	// ƒpƒ‰ƒ[ƒ^î•ñ
	parameterBamboo_ = dynamic_cast<ParameterGimmickGrowingBamboo*>(GetParameterGimmickPtr());
	assert(parameterBamboo_ != nullptr);
}

GimmickGrowingBamboo::~GimmickGrowingBamboo()
{
}

void GimmickGrowingBamboo::Init()
{
}

void GimmickGrowingBamboo::Update()
{
}
