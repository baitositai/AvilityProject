#include "ParameterEffect.h"

ParameterEffect::ParameterEffect() :
	 tag_(CollisionTags::TAG::MAX),
	isLoop_(false)
{
}

ParameterEffect::~ParameterEffect()
{
}

void ParameterEffect::LoadParameter(const Json& parameter)
{
}
