#include "../Common/Animation.h"
#include "EffectBase.h"

EffectBase::EffectBase(Parameter* parameter, const std::vector<std::string>& componentNameList, std::unique_ptr<Animation> animation) :
	ActorBase(parameter, componentNameList, std::move(animation))
{
}

EffectBase::~EffectBase()
{
}
