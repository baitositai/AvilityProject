#include "../../Manager/Common/SoundManager.h"
#include "../../Object/Character/CharacterBase.h"
#include "ComponentCharacterStateBase.h"


ComponentCharacterStateBase::ComponentCharacterStateBase(CharacterBase& owner) :
	soundManager_(SoundManager::GetInstance()),
	ComponentBase(owner)
{
}

ComponentCharacterStateBase::~ComponentCharacterStateBase()
{
}