#include "../../Manager/Common/InputManager.h"
#include "../../Manager/Common/SpriteEffectManager.h"
#include "../../Object/Character/Player.h"
#include "../../Object/Effect/EffectAirslash.h"
#include "ComponentAvilityAirslash.h"

ComponentAvilityAirslash::ComponentAvilityAirslash(Player& owner) :
	ComponentAvilityBase(owner)
{
}

ComponentAvilityAirslash::~ComponentAvilityAirslash()
{
}

void ComponentAvilityAirslash::Update()
{
	if (parameter_.jumpCount_ > 0)
	{
		// 入力がある場合
		if (inputManager_.IsTrgDown(InputManager::TYPE::PLAYER_JUMP))
		{
			// エフェクトを生成
			CreateAirslash();
		}
	}
}

void ComponentAvilityAirslash::CreateAirslash()
{
	constexpr int CREATE_NUM = 2;
	const Vector2F DIR[CREATE_NUM] = {
		{0.5f, -1.0f },
		{0.5f, 1.0f }
	};
	for (int i = 0; i < CREATE_NUM; i++)
	{
		std::unique_ptr<ParameterEffect> parameter = std::make_unique<ParameterEffect>();
		parameter->pos_ = parameter_.pos_;
		parameter->gravityDir_ = parameter_.gravityDir_;
		parameter->angle_ = parameter_.angle_;
		parameter->hitRadius_ = 20.0f;
		parameter->resourceKey_ = "airslash";
		parameter->scale_ = 1.0f;
		parameter->transparent_ = true;
		std::unique_ptr<EffectAirslash> effect = std::make_unique<EffectAirslash>(std::move(parameter), DIR[i]);
		SpriteEffectManager::GetInstance().Add(std::move(effect));
	}
}
