#pragma once
#include "UiEventBase.h"

class UiMission : public UiEventBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	UiMission(const EventBase& event);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~UiMission() override;

	/// <summary>
	/// 初期化
	/// </summary>
	void Init() override;

private:



};

