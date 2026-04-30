#include "../../Manager/Common/SceneManager.h"
#include "../../Object/Character/CharacterBase.h"
#include "ComponentInvincible.h"

ComponentInvincible::ComponentInvincible(CharacterBase& owner) :
	owner_(owner),
	sceneManager_(SceneManager::GetInstance()),
	ComponentBase(&owner)
{
}

ComponentInvincible::~ComponentInvincible()
{
}

void ComponentInvincible::Update()
{
	// –³“G’†
	if (owner_.IsInvincible())
	{
		// –³“GŽžŠÔ‚ðŒ¸‚ç‚·
		owner_.SetIsInvincibleTime(owner_.GetInvincibleTime() - sceneManager_.GetDeltaTime());
	}
}