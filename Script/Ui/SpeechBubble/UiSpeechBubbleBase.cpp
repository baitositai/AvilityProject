#include "../../Manager/Common/SceneManager.h"
#include "UiSpeechBubbleBase.h"

UiSpeechBubbleBase::UiSpeechBubbleBase(const Vector2F& followPos) :
	followPos_(followPos), 
	sceneManager_(SceneManager::GetInstance())
{
}

UiSpeechBubbleBase::~UiSpeechBubbleBase()
{
}

void UiSpeechBubbleBase::Init()
{
}

void UiSpeechBubbleBase::Update()
{
}
