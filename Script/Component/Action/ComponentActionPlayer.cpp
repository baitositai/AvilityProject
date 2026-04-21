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
	// à⁄ìÆó ÇÃèâä˙âª
	moveAmount_ = {};

	// ì¸óÕèàóù
	ProcessInputMove();

	// à⁄ìÆó ÇÃçXêV
	owner_.SetMoveAmount(moveAmount_);
}

void ComponentActionPlayer::ProcessInputMove()
{
	const float moveSpeed = owner_.GetParameter()->moveSpeed;

	// ç∂âEà⁄ìÆ
	if (inputManager_.IsNew(InputManager::TYPE::PLAYER_MOVE_RIGHT))
	{
		moveAmount_.x += moveSpeed;
	}
	else if (inputManager_.IsNew(InputManager::TYPE::PLAYER_MOVE_LEFT))
	{
		moveAmount_.x -= moveSpeed;
	}

	if (inputManager_.IsNew(InputManager::TYPE::PLAYER_MOVE_UP))
	{
		moveAmount_.y -= moveSpeed;
	}
	else if (inputManager_.IsNew(InputManager::TYPE::PLAYER_MOVE_DOWN))
	{
		moveAmount_.y += moveSpeed;
	}
}
