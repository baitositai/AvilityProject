#include "../../Common/Vector2F.h"
#include "../../Manager/Common/InputManager.h"
#include "../../Object/Character/CharacterBase.h"
#include "ComponentActionPlayer.h"

ComponentActionPlayer::ComponentActionPlayer(CharacterBase& owner) :
	ComponentActionBase(owner),
	inputManager_(InputManager::GetInstance())
{
}

ComponentActionPlayer::~ComponentActionPlayer()
{
}

void ComponentActionPlayer::Update()
{
	// “ü—Íˆ—
	ProcessInputMove();

	// ˆÚ“®—Ê‚ÌXV
	owner_.SetMoveAmount(moveAmount_);
}

void ComponentActionPlayer::ProcessInputMove()
{
	// ¶‰EˆÚ“®
	if (inputManager_.IsNew(InputManager::TYPE::PLAYER_MOVE_RIGHT))
	{
		moveAmount_.x += 1.0f;
	}
	else if (inputManager_.IsNew(InputManager::TYPE::PLAYER_MOVE_LEFT))
	{
		moveAmount_.x -= 1.0f;
	}
}
