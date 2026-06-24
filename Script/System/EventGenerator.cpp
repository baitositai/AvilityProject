#include <DxLib.h>
#include "../Utility/UtilityLoad.h"
#include "Event/EventTargetDestroy.h"
#include "Event/EventTimeLimitDefeatAll.h"
#include "Event/EventTreasureChest.h"
#include "EventGenerator.h"

EventGenerator::EventGenerator()
{
	// 生成処理の登録
	createEventMap_.emplace(EventTypes::TYPE::TARGET_DESTROY, [this]()
		{
			return CreateEventTargetDestroy();
		});
	createEventMap_.emplace(EventTypes::TYPE::TIME_LIMIT_DEFEAT_ALL, [this]()
		{
			return CreateEventTimeLimitDefeatAll();
		});
	createEventMap_.emplace(EventTypes::TYPE::TREASURE_CHEST, [this]()
		{
			return CreateEventTreasureChest();
		});
}

EventGenerator::~EventGenerator()
{
}

void EventGenerator::InitParameter()
{
	// 情報の取得
	const auto jsonParameterMap = UtilityLoad::GetJsonMapArrayData("EventParameter");

	// パラメータの取得
	const auto jsonTargetDestroyParameter = jsonParameterMap.at("targetDestroy").front();
	auto parameterTargetDetroy = std::make_unique<ParameterEventTargetDestroy>();
	parameterTargetDetroy->LoadParameter(jsonTargetDestroyParameter);
	templateParameterMap_.emplace(EventTypes::TYPE::TARGET_DESTROY, std::move(parameterTargetDetroy));

	const auto jsonTimeLimitDefeatAllParameter = jsonParameterMap.at("timeLimitDefeatAll").front();
	auto parameterTimeLimitDefeatAll = std::make_unique<ParameterEventTimeLimitDefeatAll>();
	parameterTimeLimitDefeatAll->LoadParameter(jsonTimeLimitDefeatAllParameter);
	templateParameterMap_.emplace(EventTypes::TYPE::TIME_LIMIT_DEFEAT_ALL, std::move(parameterTimeLimitDefeatAll));

	const auto jsonTreasureChestParameter = jsonParameterMap.at("treasureChest").front();
	auto parameterTreasureChest = std::make_unique<ParameterEventTimeLimitDefeatAll>();
	parameterTreasureChest->LoadParameter(jsonTreasureChestParameter);
	templateParameterMap_.emplace(EventTypes::TYPE::TREASURE_CHEST, std::move(parameterTreasureChest));
}

std::list<std::unique_ptr<EventBase>> EventGenerator::CreateEventList(const std::vector<Vector2F>& triggerPositionsList)
{
	std::list<std::unique_ptr<EventBase>> eventList;
	for (const Vector2F& pos : triggerPositionsList)
	{
		// 種類
		EventTypes::TYPE type = static_cast<EventTypes::TYPE>(GetRand(EventTypes::TYPE_MAX - 1));
		//type = EventTypes::TYPE::TREASURE_CHEST;

		// イベント生成
		auto event = CreateGameEvent(type);

		// トリガー座標設定
		event->SetTriggerPos(pos);

		// リストに格納
		eventList.push_back(std::move(event));
	}
	// リストを返す
	return eventList;
}

std::unique_ptr<EventBase> EventGenerator::CreateGameEvent(const EventTypes::TYPE type)
{
	// 必要とするものがあるか探索
	auto it = createEventMap_.find(type);

	// ある場合
	if (it != createEventMap_.end())
	{
		// 生成したものを返す
		return it->second();
	}

	// 見つからない場合空で返す
	return nullptr;
}

std::unique_ptr<EventTargetDestroy> EventGenerator::CreateEventTargetDestroy()
{
	// 専用のパラメータにキャスト
	auto parameterBase = templateParameterMap_.at(EventTypes::TYPE::TARGET_DESTROY).get();
	auto parameterEventTargetDestroy = dynamic_cast<ParameterEventTargetDestroy*>(parameterBase);

	// 空の場合
	if (parameterEventTargetDestroy == nullptr)
	{
		// 空で返す
		return nullptr;
	}

	// 生成したものを返す
	auto parameter = std::make_unique<ParameterEventTargetDestroy>(*parameterEventTargetDestroy);
	return std::make_unique<EventTargetDestroy>(std::move(parameter));
}

std::unique_ptr<EventTimeLimitDefeatAll> EventGenerator::CreateEventTimeLimitDefeatAll()
{
	// 専用のパラメータにキャスト
	auto parameterBase = templateParameterMap_.at(EventTypes::TYPE::TIME_LIMIT_DEFEAT_ALL).get();
	auto parameterEventTimeLimitDefeatAll = dynamic_cast<ParameterEventTimeLimitDefeatAll*>(parameterBase);

	// 空の場合
	if (parameterEventTimeLimitDefeatAll == nullptr)
	{
		// 空で返す
		return nullptr;
	}

	// 生成したものを返す
	auto parameter = std::make_unique<ParameterEventTimeLimitDefeatAll>(*parameterEventTimeLimitDefeatAll);
	return std::make_unique<EventTimeLimitDefeatAll>(std::move(parameter));
}

std::unique_ptr<EventTreasureChest> EventGenerator::CreateEventTreasureChest()
{
	return std::make_unique<EventTreasureChest>(std::move(std::make_unique<ParameterEvent>(*templateParameterMap_.at(EventTypes::TYPE::TREASURE_CHEST))));
}
