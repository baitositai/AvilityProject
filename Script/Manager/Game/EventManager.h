#pragma once
#include <memory>
#include <functional>
#include <unordered_map>	
#include "../../Template/Singleton.h"
#include "../../Common/Vector2F.h"

class EventBase;
class EventGenerator;

class EventManager : public Singleton<EventManager>
{
	//シングルトンにだけ共有する
	friend class Singleton<EventManager>;

public:

	/// <summary>
	/// イベントの生成
	/// </summary>
	/// <param name="triggerPositionsList">イベント発生トリガー位置リスト</param>
	void Create(const std::vector<Vector2F>& triggerPositionsList);

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

private:

	// イベントに関するリスト
	std::list<std::unique_ptr<EventBase>> eventList_;

	// イベントの生成
	std::unique_ptr<EventGenerator> eventGenerator_;

	// コンストラクタ
	EventManager();

	// デストラクタ
	~EventManager();
};