#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Common/SoundManager.h"
#include "../../Manager/Common/InputManager.h"
#include "../../Manager/Common/SpriteEffectManager.h"
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
	bool isInput = false;

	// 重力の変更
	if (inputManager_.IsTrgDown(InputManager::TYPE::AVILITY_GRAVITY_RIGHT, parameter_.padNo_))
	{
		parameter_.gravityDir_ = ParameterActor::DIR::RIGHT;
		isInput = true;
	}
	else if (inputManager_.IsTrgDown(InputManager::TYPE::AVILITY_GRAVITY_LEFT, parameter_.padNo_))
	{
		parameter_.gravityDir_ = ParameterActor::DIR::LEFT;
		isInput = true;
	}
	else if (inputManager_.IsTrgDown(InputManager::TYPE::AVILITY_GRAVITY_UP, parameter_.padNo_))
	{
		parameter_.gravityDir_ = ParameterActor::DIR::UP;
		isInput = true;
	}
	else if (inputManager_.IsTrgDown(InputManager::TYPE::AVILITY_GRAVITY_DOWN, parameter_.padNo_))
	{
		parameter_.gravityDir_ = ParameterActor::DIR::DOWN;
		isInput = true;
	}

	if (isInput)
	{
		// 角度をつける
		parameter_.angle_ = UtilityCommon::GetGravityDirRadAngle(parameter_.gravityDir_);

		// クールタイム設定
		coolTime_ = COOL_TIME;

		// 地面判定
		parameter_.isGround_ = false;

		// SE再生
		soundManager_.PlaySe(SoundType::SE::ABILITY_GRAVITY_CHANGE);

		// エフェクトを再生
		SpriteEffectManager::CreateParameter parameter;
		parameter.pos = parameter_.pos_;
		parameter.angle = parameter_.angle_;
		parameter.resourceKey = "changeGravity";
		parameter.animationSpeed = 0.2f;
		effectManager_.Create(parameter);
	}
}
