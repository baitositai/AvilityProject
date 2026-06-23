#include "../../Application.h"
#include "../../Manager/Game/PlayerManager.h"
#include "../../Object/Character/Player.h"
#include "UiPlayerBase.h"

UiPlayerBase::UiPlayerBase(const Player& owner):
	owner_(owner)
{
	playerNum_ = 1;
	basePos_ = {};
}

UiPlayerBase::~UiPlayerBase()
{
}

void UiPlayerBase::Init()
{
	constexpr int OFFSET = 300;

	// 番号取得
	playerNum_ = static_cast<int>(owner_.GetParameter().padNo_) - 1;

	// ベース位置
	basePos_ = {
		Application::SCREEN_SIZE_X / (PlayerManager::PLAYER_MAX + 1) + OFFSET * playerNum_,
		Application::SCREEN_SIZE_Y - 45
	};
}

void UiPlayerBase::Update()
{
	CheckOwnerDead();
}

bool UiPlayerBase::CheckOwnerDead()
{
	if (owner_.IsDelete())
	{
		isDelete_ = true;
		isActive_ = false;
	}
	return isDelete_;
}
