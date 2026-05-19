#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Common/InputManager.h"
#include "../../Object/Character/Player.h"
#include "../../Utility/UtilityCommon.h"
#include "ComponentAvilityGravity.h"

ComponentAvilityGravity::ComponentAvilityGravity(Player& owner) :
	ComponentAvilityBase(owner)
{
	coolTime_ = 0.0f;
	abilitySlot_ = ABILITY_SLOT::FIRST;
	type_ = AvilityTypes::TYPE::GRAVITY;
}

ComponentAvilityGravity::~ComponentAvilityGravity()
{

}

void ComponentAvilityGravity::Update()
{
	// クールタイムが0以下の場合
	if (coolTime_ > 0.0f)
	{
		coolTime_ -= sceneManager_.GetDeltaTime();
		return;
	}

	// 入力処理
	ProcessGravity();
}

void ComponentAvilityGravity::Remove()
{
	// 重力方向を下に戻す
	if (parameter_.gravityDir_ != ParameterActor::DIR::DOWN)
	{
		parameter_.gravityDir_ = ParameterActor::DIR::DOWN;
		parameter_.isGround_ = false;
	}
}

void ComponentAvilityGravity::ProcessGravity()
{
	if (inputManager_.IsTrgDown(InputManager::TYPE::AVILITY_GRAVITY_RIGHT))
	{
		parameter_.gravityDir_ = ParameterActor::DIR::RIGHT;
		parameter_.angle_ = UtilityCommon::Deg2RadF(270.0f);
		coolTime_ = COOL_TIME;
		parameter_.isGround_ = false;
	}
	else if (inputManager_.IsTrgDown(InputManager::TYPE::AVILITY_GRAVITY_LEFT))
	{
		parameter_.gravityDir_ = ParameterActor::DIR::LEFT;
		parameter_.angle_ = UtilityCommon::Deg2RadF(90.0f);
		coolTime_ = COOL_TIME;
		parameter_.isGround_ = false;
	}
	else if (inputManager_.IsTrgDown(InputManager::TYPE::AVILITY_GRAVITY_UP))
	{
		parameter_.gravityDir_ = ParameterActor::DIR::UP;
		parameter_.angle_ = UtilityCommon::Deg2RadF(180.0f);
		coolTime_ = COOL_TIME;
		parameter_.isGround_ = false;
	}
	else if (inputManager_.IsTrgDown(InputManager::TYPE::AVILITY_GRAVITY_DOWN))
	{
		parameter_.gravityDir_ = ParameterActor::DIR::DOWN;
		parameter_.angle_ = UtilityCommon::Deg2RadF(0.0f);
		coolTime_ = COOL_TIME;
		parameter_.isGround_ = false;
	}
}
