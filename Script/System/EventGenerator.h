#pragma once
#include <memory>
#include <list>
#include <vector>
#include <functional>
#include <unordered_map>
#include "../../Manager/Game/EventTypes.h"
#include "../../Common/Vector2F.h"

class EventBase;
class EventTargetDestroy;
class EventTimeLimitDefeatAll;

class ParameterEvent;

class EventGenerator
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	EventGenerator();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EventGenerator();

	/// <summary>
	/// パラメータ情報を初期化
	/// </summary>
	void InitParameter();

	/// <summary>
	/// イベントリストを生成
	/// </summary>
	/// <param name="triggerPositionsList">イベント発生トリガー位置リスト</param>
	/// <returns>イベントリスト</returns>
	std::list<std::unique_ptr<EventBase>> CreateEventList(const std::vector<Vector2F>& triggerPositionsList);

	/// <summary>
	/// イベントの生成
	/// </summary>
	/// <param name="type">種類</param>
	/// <returns>イベントのインスタンス</returns>
	std::unique_ptr<EventBase> CreateGameEvent(const EventTypes::TYPE type);

private:

	// イベントの生成マップ
	std::unordered_map<EventTypes::TYPE, std::function<std::unique_ptr<EventBase>()>> createEventMap_;

	// テンプレートとなるパラメータマップ
	std::unordered_map<EventTypes::TYPE, std::unique_ptr<ParameterEvent>> templateParameterMap_;

	// 各種イベントの生成処理
	std::unique_ptr<EventTargetDestroy> CreateEventTargetDestroy();
	std::unique_ptr<EventTimeLimitDefeatAll> CreateEventTimeLimitDefeatAll();
};