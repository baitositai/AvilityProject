#include "../../Manager/Common/ResourceManager.h"
#include "../../Resource/ResourceSprite.h"
#include "../../Utility/UtilityCommon.h"
#include "UiTimer.h"

UiTimer::UiTimer()
{
	drawCount_ = -1;
	numberHandle_ = nullptr;
	defaultNumberSize_ = {};
	numberSize_ = {};
}

UiTimer::~UiTimer()
{
}

void UiTimer::Init()
{
	numberHandle_ = resourceManager_.GetHandles("numbers");
	defaultNumberSize_ = resourceManager_.GetResourceSprite("numbers")->GetSize();
	drawCount_ = 0;
}

void UiTimer::Draw()
{
	int digitCount = UtilityCommon::GetDigitCount(drawCount_);

	// Œ…”•ª‰ñ‚·
	for (int i = 0; i < digitCount; i++)
	{
		// •`‰æ‚·‚é”š
		int index = 0;

		// ’l‚ÌŒˆ’è
		int divisor = 1;
		for (int j = 0; j < (digitCount - 1 - i); j++)
		{
			divisor *= 10;
		}
		index = (drawCount_ / divisor) % 10;

		// •`‰æ
		DrawRotaGraph(
			numberStartDrawPos_.x + i * numberSize_.x,
			numberStartDrawPos_.y,
			scale_,
			0.0f,
			numberHandle_[index],
			true
		);
	}
}

void UiTimer::SetNumber(const int number)
{
	drawCount_ = number;
}

void UiTimer::SetParameter(const Vector2& pos, const int drawCount, const float scale)
{	
	// ’l‚Ìİ’è
	drawCount_ = drawCount;
	pos_ = pos;
	scale_ = scale;
	numberSize_ = Vector2F::MulVector2FFloat(defaultNumberSize_.ToVector2F(), scale_).ToVector2();

	// ’†S‚É•`‰æ‚·‚é‚æ‚¤‚ÉˆÊ’u‚ğ’²®
	int digitCount = UtilityCommon::GetDigitCount(drawCount_);
	numberStartDrawPos_.x = pos_.x - numberSize_.x * digitCount / 2;
	numberStartDrawPos_.y = pos_.y - numberSize_.y / 2;
}