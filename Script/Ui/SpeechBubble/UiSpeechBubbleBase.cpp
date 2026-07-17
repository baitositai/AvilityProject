#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Common/Camera.h"
#include "UiSpeechBubbleBase.h"

UiSpeechBubbleBase::UiSpeechBubbleBase(const Vector2F& followPos) :
	followPos_(followPos), 
	sceneManager_(SceneManager::GetInstance())
{
	localPos_ = {};
	scaleUpSpeed_ = 0.0f;
}

UiSpeechBubbleBase::~UiSpeechBubbleBase()
{
}

void UiSpeechBubbleBase::Init()
{
	localPos_ = { 60, -80 };
	scaleUpSpeed_ = 0.08f;
}

void UiSpeechBubbleBase::Update()
{
}

void UiSpeechBubbleBase::Draw()
{
	if (isActive_)
	{
		Vector2F cameraPos = mainCamera.GetPos();
		Vector2 drawPos = cameraPos.ToVector2() + pos_;
		DrawRotaGraph(
			drawPos.x,
			drawPos.y,
			scale_,
			angle_,
			handle_,
			true
		);
	}
}
