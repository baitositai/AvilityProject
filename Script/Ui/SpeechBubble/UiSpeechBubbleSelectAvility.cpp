#include "../../Manager/Common/SceneManager.h"
#include "../../Object/Character/Player.h"
#include "UiSpeechBubbleSelectAvility.h"

UiSpeechBubbleSelectAvility::UiSpeechBubbleSelectAvility(const Player& owner) :
	owner_(owner),
	UiSpeechBubbleBase(owner.GetParameter().pos_)
{
}

UiSpeechBubbleSelectAvility::~UiSpeechBubbleSelectAvility()
{
}

void UiSpeechBubbleSelectAvility::Init()
{
}

void UiSpeechBubbleSelectAvility::Update()
{
	// ägëÂèàóù
	if (scale_ < 1.0f) { scale_ += scaleUpSpeed_; }

	// ç¿ïWÇÃí«è]
	pos_ = Vector2F::AddVector2F(followPos_, localPos_).ToVector2();

	// éûä‘èàóù
	timer_ += sceneManager_.GetDeltaTime();
	if (displayTime_ < timer_)
	{
		Delete();
	}
}
