#include "../Common/Animation.h"
#include "EffectBase.h"

EffectBase::EffectBase(std::unique_ptr<ParameterEffect> parameter) :
	 ActorBase(std::move(parameter))
{
	// ƒpƒ‰ƒ[ƒ^
	parameterEffect_ = dynamic_cast<ParameterEffect*>(GetParameterActorPtr());
	assert(parameterEffect_ != nullptr);
}

EffectBase::~EffectBase()
{
}
