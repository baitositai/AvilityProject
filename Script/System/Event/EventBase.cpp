#include "../../Application.h"
#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Common/SoundManager.h"
#include "../../Manager/Common/Camera.h"
#include "../../Manager/Game/EventManager.h"
#include "../../Manager/Game/EnemyManager.h"
#include "../../Manager/Game/GimmickManager.h"
#include "../../Manager/Game/UiManager.h"
#include "../../Ui/Event/UiMission.h"
#include "../../Ui/Event/UiMissionMessage.h"
#include "../../Ui/Common/UiTimer.h"
#include "EventBase.h"

EventBase::EventBase(std::unique_ptr<ParameterEvent> parameter) :
	sceneManager_(SceneManager::GetInstance()),
	eventManager_(EventManager::GetInstance()),
	enemyManager_(EnemyManager::GetInstance()),
	gimmickManager_(GimmickManager::GetInstance()),
	soundManager_(SoundManager::GetInstance()),
	uiManager_(UiManager::GetInstance()),
	parameter_(std::move(parameter))
{
	state_ = STATE::START;
	isDelete_ = false;
	triggerPos_ = {};
	eventType_ = EventTypes::TYPE::MAX;	
	timeLimit_ = 0.0f;
	isDeleteUi_ = false;

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
	// カメラ座標を取得
	Vector2F cameraPos = mainCamera.GetPos();

	// トリガーの画面上の位置（スクリーン座標）を算出
	Vector2 screenTriggerPos = Vector2::AddVector2(triggerPos_.ToVector2(), cameraPos.ToVector2());

	// 判定の中心となる画面基準位置
	constexpr int TARGET_SCREEN_X = Application::SCREEN_HALF_X;
	constexpr int TARGET_SCREEN_Y = Application::SCREEN_SIZE_Y - GROUND_OFFSET;

	// ターゲット位置が指定の矩形範囲内にあるか判定
	if (screenTriggerPos.x >= TARGET_SCREEN_X - OFFSET_X &&
		screenTriggerPos.x <= TARGET_SCREEN_X + OFFSET_X &&
		screenTriggerPos.y >= TARGET_SCREEN_Y - OFFSET_Y &&
		screenTriggerPos.y <= TARGET_SCREEN_Y + OFFSET_Y)
	{
		ChangeState(STATE::CHALLENGE);
		soundManager_.PlaySe(SoundType::SE::EVENT_START);
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

void EventBase::CreateUi()
{
	auto mission = std::make_unique<UiMission>(*this);
	uiManager_.Add(std::move(mission));
	
	auto missionMessage = std::make_unique<UiMissionMessage>(*this);
	uiManager_.Add(std::move(missionMessage));
}