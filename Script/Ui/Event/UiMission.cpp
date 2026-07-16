#include "../../Application.h"
#include "../../Manager/Common/ResourceManager.h"
#include "UiMission.h"

UiMission::UiMission(const EventBase& event) :
	UiEventBase(event)
{
}

UiMission::~UiMission()
{
}

void UiMission::Init()
{
	// 描画位置の設定
	pos_ = { Application::SCREEN_HALF_X, 136 };

	// リソース取得
	handle_ = resourceManager_.GetHandle("uiMission");
}
