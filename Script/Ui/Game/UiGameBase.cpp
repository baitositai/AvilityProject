#include <DxLib.h>
#include "../../Manager/Common/ResourceManager.h"
#include "../../Utility/UtilityCommon.h"
#include "UiGameBase.h"

UiGameBase::UiGameBase()
{
	drawCount_ = -1;
	numberHandle_ = nullptr;
	numberScale_ = 0.0f;

}

UiGameBase::~UiGameBase()
{
}

void UiGameBase::Draw()
{
	UiBase::Draw();

	DrawNumber();
}

void UiGameBase::InitNumber()
{
	numberHandle_ = resourceManager_.GetHandles("numbers");
	numberSize_ = { 32,32 };
	numberScale_ = 0.25f;
	numberStartDrawPos_ = pos_;
	numberStartDrawPos_.x = 350;
}

void UiGameBase::DrawNumber()
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
			numberScale_,
			0.0f,
			numberHandle_[index],
			true
		);
	}
}
