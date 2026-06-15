#pragma once
#include "EventBase.h"

class EventTreasureChest : public EventBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	EventTreasureChest(std::unique_ptr<ParameterEvent> parameter);
	
	/// <summary>
	/// デストラクタ
	/// </summary>
	~EventTreasureChest() override;

private:

	// 制限時間
	float timeLimit_;

	// 状態別更新処理
	void UpdateChallenge() override;
	void UpdateEnd() override;

	// 状態線処理
	void ChangeStateChallenge() override;
};