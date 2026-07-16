#pragma once
#include <memory>
#include "UiEventBase.h"
#include "../../Manager/Game/EventTypes.h"

class UiTimer;

class UiMissionMessage : public UiEventBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	UiMissionMessage(const EventBase& event);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~UiMissionMessage() override;

	/// <summary>
	/// 初期化
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() override;

private:
	int* messageHandle_;

	std::unique_ptr<UiTimer> uiTimer_;

};