#include "../../Manager/Common/SceneManager.h"
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