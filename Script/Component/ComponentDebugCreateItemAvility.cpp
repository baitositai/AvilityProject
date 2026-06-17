#include <DxLib.h>
#include "../../Utility/UtilityCommon.h"
#include "../../Manager/Common/InputManager.h"
#include "../../Manager/Game/ItemManager.h"
#include "../../Object/Item/ItemAvility.h"
#include "../../Object/Character/Player.h"
#include "Avility/AvilityTypes.h"
#include "ComponentDebugCreateItemAvility.h"

ComponentDebugCreateItemAvility::ComponentDebugCreateItemAvility(Player& owner) :
	ComponentBase(owner),
	inputManager_(InputManager::GetInstance()),
	playerOwner_(owner)
{
	type_ = 0;
}

ComponentDebugCreateItemAvility::~ComponentDebugCreateItemAvility()
{
}

void ComponentDebugCreateItemAvility::Update()
{
	Input::JOYPAD_NO padNo = playerOwner_.GetParameter().padNo_;

	if (inputManager_.IsTrgDown(InputManager::TYPE::DEBUG_CREATE_ITEM_AVILITY, padNo))
	{
		Vector2F pos = Vector2F::AddVector2F(owner_.GetParameter().pos_, Vector2F::MulVector2FFloat(owner_.GetParameter().GetFront(), 80.0f));
		ItemManager::GetInstance().CreateAvilityItem(static_cast<AvilityTypes::TYPE>(type_), pos);
	}
	else if (inputManager_.IsTrgDown(InputManager::TYPE::DEBUG_SELECT_RIGHT_ITEM_AVILITY, padNo))
	{
		type_ = UtilityCommon::WrapStepIndex(type_, 1, 0, static_cast<int>(AvilityTypes::TYPE::MAX));
	}
	else if (inputManager_.IsTrgDown(InputManager::TYPE::DEBUG_SELECT_LEFT_ITEM_AVILITY, padNo))
	{
		type_ = UtilityCommon::WrapStepIndex(type_, -1, 0, static_cast<int>(AvilityTypes::TYPE::MAX));
	}
}

void ComponentDebugCreateItemAvility::DebugDraw()
{
	Vector2 pos = owner_.GetParameter().drawPos_;
	Vector2 hitSize = owner_.GetParameter().hitSize_;

	const std::wstring abilityName =
		UtilityCommon::GetWStringFromString(
			AvilityTypes::AVILITY_NAME_MAP.at(static_cast<AvilityTypes::TYPE>(type_)));

	DrawFormatString(
		pos.x - hitSize.x / 2,
		pos.y - hitSize.y / 2 - 60,
		UtilityCommon::RED,
		L"Å©Å@%lsÅ@Å®",
		abilityName.c_str());
}