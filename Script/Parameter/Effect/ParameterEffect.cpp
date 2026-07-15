#include "ParameterEffect.h"

ParameterEffect::ParameterEffect() :
	 tag_(CollisionTags::TAG::MAX),
	isLoop_(false),
	id_(-1)
{
}

ParameterEffect::~ParameterEffect()
{
}

void ParameterEffect::LoadParameter(const Json& parameter)
{
}
