#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Common/SoundManager.h"
#include "../../Manager/Common/InputManager.h"
#include "../../Object/Character/Player.h"
#include "../../Utility/UtilityCommon.h"
#include "ComponentAvilityGravity.h"

ComponentAvilityGravity::ComponentAvilityGravity(Player& owner) :
	ComponentAvilityBase(owner)
{
	coolTime_ = 0.0f;
	type_ = AvilityTypes::TYPE::GRAVITYCONTROLL;
}

ComponentAvilityGravity::~ComponentAvilityGravity()
{

}

void ComponentAvilityGravity::Create()
{
	ComponentAvilityBase::Create();
	Init();
}

void ComponentAvilityGravity::Init()
{
	coolTime_ = 0.0f;
}

void ComponentAvilityGravity::Update()
{
	// クールタイムが0より大きい場合
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

	ComponentAvilityBase::Remove();
}

void ComponentAvilityGravity::ProcessGravity()
{
	if (inputManager_.IsTrgDown(InputManager::TYPE::AVILITY_GRAVITY_RIGHT, parameter_.padNo_))
	{
		parameter_.gravityDir_ = ParameterActor::DIR::RIGHT;
		parameter_.angle_ = UtilityCommon::GetGravityDirRadAngle(parameter_.gravityDir_);
		coolTime_ = COOL_TIME;
		parameter_.isGround_ = false;
		soundManager_.PlaySe(SoundType::SE::ABILITY_GRAVITY_CHANGE);
	}
	else if (inputManager_.IsTrgDown(InputManager::TYPE::AVILITY_GRAVITY_LEFT, parameter_.padNo_))
	{
		parameter_.gravityDir_ = ParameterActor::DIR::LEFT;
		parameter_.angle_ = UtilityCommon::GetGravityDirRadAngle(parameter_.gravityDir_);
		coolTime_ = COOL_TIME;
		parameter_.isGround_ = false;
		soundManager_.PlaySe(SoundType::SE::ABILITY_GRAVITY_CHANGE);
	}
	else if (inputManager_.IsTrgDown(InputManager::TYPE::AVILITY_GRAVITY_UP, parameter_.padNo_))
	{
		parameter_.gravityDir_ = ParameterActor::DIR::UP;
		parameter_.angle_ = UtilityCommon::GetGravityDirRadAngle(parameter_.gravityDir_);
		coolTime_ = COOL_TIME;
		parameter_.isGround_ = false;
		soundManager_.PlaySe(SoundType::SE::ABILITY_GRAVITY_CHANGE);
	}
	else if (inputManager_.IsTrgDown(InputManager::TYPE::AVILITY_GRAVITY_DOWN, parameter_.padNo_))
	{
		parameter_.gravityDir_ = ParameterActor::DIR::DOWN;
		parameter_.angle_ = UtilityCommon::GetGravityDirRadAngle(parameter_.gravityDir_);
		coolTime_ = COOL_TIME;
		parameter_.isGround_ = false;
		soundManager_.PlaySe(SoundType::SE::ABILITY_GRAVITY_CHANGE);
	}
}
