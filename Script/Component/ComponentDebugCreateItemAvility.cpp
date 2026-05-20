#include <DxLib.h>
#include "../../Utility/UtilityCommon.h"
#include "../../Manager/Common/InputManager.h"
#include "../../Manager/Game/ItemManager.h"
#include "../../Object/Item/ItemAvility.h"
#include "../../Object/ActorBase.h"
#include "Avility/AvilityTypes.h"
#include "ComponentDebugCreateItemAvility.h"

ComponentDebugCreateItemAvility::ComponentDebugCreateItemAvility(ActorBase& owner) :
	ComponentBase(owner),
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
		std::unique_ptr<ParameterItemAvility> parameter = std::make_unique<ParameterItemAvility>();
		parameter->type_ = static_cast<AvilityTypes::TYPE>(type_);
		parameter->pos_ = Vector2F::AddVector2F(owner_.GetParameter().pos_, Vector2F::MulVector2FFloat(owner_.GetParameter().GetFront(), 50.0f));
		parameter->hitRadius_ = RADIUS;
		parameter->hitSize_ = Vector2(RADIUS, RADIUS);
		parameter->gravityPower_ = 9.8f;
		parameter->gravityDir_ = ParameterActor::DIR::DOWN;
		parameter->componentkeys_ = { "gravity", "move" };
		ItemManager::GetInstance().Add(std::make_unique<ItemAvility>(std::move(parameter)));
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
	Vector2F posF = owner_.GetParameter().pos_;
	Vector2 pos = posF.ToVector2();
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