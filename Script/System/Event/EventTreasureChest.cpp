#include "../../Manager/Game/GimmickManager.h"
#include "../../Manager/Common/SceneManager.h"
#include "EventTreasureChest.h"

EventTreasureChest::EventTreasureChest(std::unique_ptr<ParameterEvent> parameter) :
	EventBase(std::move(parameter))
{
	timeLimit_ = 0.0f;
}

EventTreasureChest::~EventTreasureChest()
{
}

void EventTreasureChest::UpdateChallenge()
{
	// ó‘Ô‘JˆÚ
	ChangeState(STATE::END);

	// •ó” oŒ»	
	GimmickManager::CreateParameter createParameter = {};
	createParameter.type = GimmickTypes::TYPE::TREASURE_CHEST;
	createParameter.pos = triggerPos_;
	gimmickManager_.Create(createParameter);
}

void EventTreasureChest::UpdateEnd()
{
	// §ŒÀŠÔˆ—
	timeLimit_ -= sceneManager_.GetDeltaTime();
	if (timeLimit_ <= 0)
	{
		// ƒJƒƒ‰ÄŠJ
		CameraRestart();

		// íœ—\’è
		isDelete_ = true;
	}
}

void EventTreasureChest::ChangeStateChallenge()
{
	EventBase::ChangeStateChallenge();

	CameraStop();
}