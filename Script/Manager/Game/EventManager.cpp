#include "../../System/Event/EventBase.h"
#include "../../System/Event/EventTargetDestroy.h"
#include "../../System/Event/EventTimeLimitDefeatAll.h"
#include "../../System/EventGenerator.h"
#include "EventManager.h"

void EventManager::Create(const std::vector<Vector2F>& triggerPositionsList)
{
	eventList_ = eventGenerator_->CreateEventList(triggerPositionsList);
}

void EventManager::Init()
{
	if (eventList_.empty()) { return; }
	
	// 初期化
	for (auto& event : eventList_)
	{
		event->Init();
	}
}

void EventManager::Update()
{
	if (eventList_.empty()) { return; }
	
	// ポインタの取得
	auto& event = eventList_.front();
	
	// 更新処理
	event->Update();

	// 削除判定
	if (event->IsDelete())
	{
		// 先頭要素を取り外す
		eventList_.pop_front();
	}
}

EventManager::EventManager()
{
	eventGenerator_ = std::make_unique<EventGenerator>();
	eventGenerator_->InitParameter();
}

EventManager::~EventManager()
{

}