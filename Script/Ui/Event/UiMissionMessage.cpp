#include <DxLib.h>
#include "../../Application.h"
#include "../../Manager/Common/ResourceManager.h"
#include "../../System/Event/EventBase.h"
#include "../Common/UiTimer.h"
#include "UiMissionMessage.h"

UiMissionMessage::UiMissionMessage(const EventBase& event) :
	UiEventBase(event)
{ 
}


UiMissionMessage::~UiMissionMessage()
{
}

void UiMissionMessage::Init()
{
	// 描画位置の設定
	pos_ = { Application::SCREEN_HALF_X, 217 };

	// リソース取得
	messageHandle_ = resourceManager_.GetHandles("uiMissionMessage");
	//handle_ = handles[static_cast<int>(eventBase_.GetType())];

	// タイマー
	uiTimer_ = std::make_unique<UiTimer>();
	uiTimer_->Init();
	uiTimer_->SetParameter(Vector2(Application::SCREEN_HALF_X, 295), static_cast<int>(eventBase_.GetTimer()), 0.375f);
}

void UiMissionMessage::Update()
{
	UiEventBase::Update();

	// タイマーの削除
	if (isDelete_)
	{
		isActive_ = false;
		uiTimer_->Delete();
	}
}

void UiMissionMessage::Draw()
{
	if (isActive_ || !eventBase_.IsDeleteUi())
	{
		DrawRotaGraph(
			pos_.x,
			pos_.y,
			scale_,
			angle_,
			messageHandle_[static_cast<int>(eventBase_.GetType())],
			true
		);
		uiTimer_->SetNumber(static_cast<int>(eventBase_.GetTimer()));
		uiTimer_->Draw();
	}
}
