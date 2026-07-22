#include <DxLib.h>
#include "../../Application.h"
#include "../../Manager/Common/ResourceManager.h"
#include "../../Manager/Game/PlayerManager.h"
#include "UiNewPlayer.h"

UiNewPlayer::UiNewPlayer() :
	playerManager_(PlayerManager::GetInstance())
{
}

UiNewPlayer::~UiNewPlayer()
{
}

void UiNewPlayer::Init()
{
	handle_ = resourceManager_.GetHandle("newPlayer");
	scale_ = 1.0f;
}

void UiNewPlayer::Draw()
{
	constexpr int OFFSET = 250;
	const int playerCount = playerManager_.GetPlayerNum();

	// •`‰æˆ—
	for (int i = playerCount; i < PlayerManager::PLAYER_MAX; i++)
	{
		pos_ = {
		Application::SCREEN_SIZE_X / (PlayerManager::PLAYER_MAX + 1) + OFFSET * i,
		Application::SCREEN_SIZE_Y - 32
		};

		DrawRotaGraph(
			pos_.x,
			pos_.y,
			scale_,
			angle_,
			handle_,
			true
		);
	}
}
