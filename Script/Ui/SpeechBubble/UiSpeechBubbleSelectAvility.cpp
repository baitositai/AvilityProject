#include "../../Manager/Common/ResourceManager.h"
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
	UiSpeechBubbleBase::Init();
	handle_ = resourceManager_.GetHandle("sbSelectAvility");
	scale_ = 0.0f;
}

void UiSpeechBubbleSelectAvility::Update()
{
	// ägëÂèàóù
	if (scale_ < 1.0f) { scale_ += scaleUpSpeed_; }

	// ç¿ïWÇÃí«è]
	pos_ = Vector2F::AddVector2F(followPos_, localPos_).ToVector2();

	// çÌèúèàóù
	if (owner_.GetParameter().selectAvilityTime_ <= 0.0f || owner_.IsDelete())
	{
		Delete();
	}
}