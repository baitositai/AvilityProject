#include <DxLib.h>
#include "../../Utility/UtilityCommon.h"
#include "../../Manager/Common/InputManager.h"
#include "../../Manager/Game/ItemManager.h"
#include "../../Object/Item/ItemAvility.h"
#include "../../Object/ActorBase.h"
#include "Avility/AvilityTypes.h"
#include "ComponentDebugCreateItemAvility.h"

ComponentDebugCreateItemAvility::ComponentDebugCreateItemAvility(ActorBase& owner) :
	ComponentBase(&owner),
	inputManager_(InputManager::GetInstance())
{
	type_ = 0;
}

ComponentDebugCreateItemAvility::~ComponentDebugCreateItemAvility()
{
}

void ComponentDebugCreateItemAvility::Update()
{
	constexpr float RADIUS = 20.0f;

	if (inputManager_.IsTrgDown(InputManager::TYPE::DEBUG_CREATE_ITEM_AVILITY))
	{
		ItemAvility::Parameter parameter = {};
		parameter.type = static_cast<AvilityTypes::TYPE>(type_);
		parameter.pos = Vector2F::AddVector2F(owner_->GetParameter()->pos, Vector2F::MulVector2FFloat(owner_->GetFront(), 50.0f));
		parameter.hitRadius = RADIUS;
		parameter.hitSize = Vector2(RADIUS, RADIUS);
		parameter.gravityPower = 9.8f;
		parameter.gravityDir = ActorBase::DIR::DOWN;

		std::vector<std::string> componentNameList = { "gravity", "move" };
		ItemManager::GetInstance().Add(std::make_unique<ItemAvility>(parameter, componentNameList));
	}
	else if (inputManager_.IsTrgDown(InputManager::TYPE::DEBUG_SELECT_RIGHT_ITEM_AVILITY))
	{
		type_ = UtilityCommon::WrapStepIndex(type_, 1, 0, static_cast<int>(AvilityTypes::TYPE::MAX));
	}
	else if (inputManager_.IsTrgDown(InputManager::TYPE::DEBUG_SELECT_LEFT_ITEM_AVILITY))
	{
		type_ = UtilityCommon::WrapStepIndex(type_, -1, 0, static_cast<int>(AvilityTypes::TYPE::MAX));
	}
}

void ComponentDebugCreateItemAvility::DebugDraw()
{
	Vector2F posF = owner_->GetParameter()->pos;
	Vector2 pos = posF.ToVector2();
	Vector2 hitSize = owner_->GetParameter()->hitSize;

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