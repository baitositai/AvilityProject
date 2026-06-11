#include "../../Application.h"
#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Common/Camera.h"
#include "../../Manager/Game/EventManager.h"
#include "../../Manager/Game/EnemyManager.h"
#include "../../Manager/Game/GimmickManager.h"
#include "EventBase.h"

EventBase::EventBase(std::unique_ptr<ParameterEvent> parameter) :
	sceneManager_(SceneManager::GetInstance()),
	eventManager_(EventManager::GetInstance()),
	enemyManager_(EnemyManager::GetInstance()),
	gimmickManager_(GimmickManager::GetInstance()),
	parameter_(std::move(parameter))
{
	state_ = STATE::START;
	isDelete_ = false;
	triggerPos_ = {};

	stateMap_.emplace(STATE::START, std::bind(&EventBase::ChangeStateStart, this));
	stateMap_.emplace(STATE::CHALLENGE, std::bind(&EventBase::ChangeStateChallenge, this));
	stateMap_.emplace(STATE::END, std::bind(&EventBase::ChangeStateEnd, this));
}

EventBase::~EventBase()
{
}

void EventBase::Init()
{
	ChangeState(STATE::START);
}

void EventBase::Update()
{
	update_();
}

void EventBase::SetTriggerPos(const Vector2F& triggerPos)
{
	triggerPos_ = triggerPos;
}

void EventBase::CameraStop()
{
	mainCamera.Stop();
}

void EventBase::CameraRestart()
{
	mainCamera.Restart();
}

void EventBase::UpdateStart()
{
	// ターゲット位置がカメラの中心より右に来た場合
	if (triggerPos_.x + mainCamera.GetPos().x < Application::SCREEN_HALF_X)
	{
		ChangeState(STATE::CHALLENGE);
	}
}

void EventBase::UpdateChallenge()
{
}

void EventBase::UpdateEnd()
{
}

void EventBase::ChangeState(const STATE state)
{
	state_ = state;

	stateMap_[state_]();
}

void EventBase::ChangeStateStart()
{
	update_ = std::bind(&EventBase::UpdateStart, this);
}

void EventBase::ChangeStateChallenge()
{
	update_ = std::bind(&EventBase::UpdateChallenge, this);
}

void EventBase::ChangeStateEnd()
{
	update_ = std::bind(&EventBase::UpdateEnd, this);
}