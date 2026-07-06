#include <DxLib.h>
#include "../../Manager/Common/ResourceManager.h"
#include "../../Object/Character/Player.h"
#include "UiPlayerAvilitySlot.h"

UiPlayerAvilitySlot::UiPlayerAvilitySlot(const Player& owner) :
	UiPlayerBase(owner)
{
	avilitySlotHandle_ = nullptr;
}

UiPlayerAvilitySlot::~UiPlayerAvilitySlot()
{
}

void UiPlayerAvilitySlot::Init()
{
	avilitySlotHandle_ = resourceManager_.GetHandles("avilityItemsSprite");

	UiPlayerBase::Init();

	//1つ目のスロット位置の設定
	Vector2 localPos = { -32, -5 };
	pos_ = Vector2::AddVector2(basePos_, localPos);
}

void UiPlayerAvilitySlot::Update()
{
	CheckOwnerDead();
}

void UiPlayerAvilitySlot::Draw()
{
	auto& avilities = owner_.GetAvilityItemResourceIndexs();
	int size = static_cast<int>(avilities.size());
	for (int i = 0; i < size; i++)
	{
		DrawRotaGraph(
			pos_.x + i * 32,
			pos_.y,
			0.75f,
			0.0f,
			avilitySlotHandle_[avilities[i]],
			true
		);
	}
}
