#include "../../Component/ComponentSpriteAnimation.h"
#include "CharacterBase.h"

CharacterBase::CharacterBase(const Parameter& parameter) :
	parameter_(parameter)
{
}

CharacterBase::~CharacterBase()
{
}

void CharacterBase::Init()
{
}

void CharacterBase::Update()
{
	spriteAnimation_->Update();
}

void CharacterBase::Draw()
{
}
