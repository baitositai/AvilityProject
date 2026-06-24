#include "../../Manager/Common/SceneManager.h"
#include "../../Object/Character/CharacterBase.h"
#include "ComponentInvincible.h"

ComponentInvincible::ComponentInvincible(CharacterBase& owner) :
	owner_(owner),
	parameter_(owner.GetParameter()),
	sceneManager_(SceneManager::GetInstance()),
	ComponentBase(owner)
{
	// ‘Ò‹@ó‘Ô‚É‘JˆÚ
	updateFunc_ = std::bind(&ComponentInvincible::Wait, this);
}

ComponentInvincible::~ComponentInvincible()
{
}

void ComponentInvincible::Update()
{
	updateFunc_();
}

void ComponentInvincible::Wait()
{
	if(owner_.IsInvincible())
	{
		// –³“Gó‘Ô‚É‘JˆÚ
		updateFunc_ = std::bind(&ComponentInvincible::SubInvincibleTime, this);
	}
}

void ComponentInvincible::SubInvincibleTime()
{
	// –³“GŠÔ‚ğŒ¸‚ç‚·
	parameter_.invincibleTime_ -= sceneManager_.GetDeltaTime();

	// ‚Ü‚¾–³“G’†‚Ìê‡
	if (owner_.IsInvincible())
	{
		// I—¹
		return;
	}

	// ‘Ò‹@ó‘Ô‚É‘JˆÚ
	updateFunc_ = std::bind(&ComponentInvincible::Wait, this);
}
