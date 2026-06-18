#include <tgmath.h>
#include "../../Manager/Common/InputManager.h"
#include "../../Manager/Common/SpriteEffectManager.h"
#include "../../Utility/UtilityCommon.h"
#include "../../Object/Character/Player.h"
#include "../../Object/Effect/EffectAirslash.h"
#include "ComponentAvilityAirslash.h"

ComponentAvilityAirslash::ComponentAvilityAirslash(Player& owner) :
	ComponentAvilityBase(owner)
{
	type_ = AvilityTypes::TYPE::AIRSLASH;
	preJumpCount_ = -1;
}

ComponentAvilityAirslash::~ComponentAvilityAirslash()
{
}

void ComponentAvilityAirslash::Create()
{	
	ComponentAvilityBase::Create();

	Init();
}

void ComponentAvilityAirslash::Init()
{	
	preJumpCount_ = parameter_.jumpCount_;
}

void ComponentAvilityAirslash::Update()
{
	// ジャンプ回数の比較
	int nowJumpCount = parameter_.jumpCount_;
	if (preJumpCount_ > 0 && !parameter_.isHitItem_)
	{
		if (inputManager_.IsTrgDown(InputManager::TYPE::PLAYER_JUMP, parameter_.padNo_))
		{
			CreateAirslash();
		}
	}
	// バックアップ保持
	preJumpCount_ = parameter_.jumpCount_;
}

void ComponentAvilityAirslash::Remove()
{
	ComponentAvilityBase::Remove();
}

void ComponentAvilityAirslash::CreateAirslash()
{
	constexpr int CREATE_NUM = 2;
	constexpr float SPREAD_WIDTH = 0.5f;

	// 基準となる重力下方向ベクトルを取得
	const Vector2F downDir = parameter_.GetDown();

	// 右方向
	const Vector2F rightDir = { -downDir.y, downDir.x };

	// 方向を調整
	const Vector2F dirRightSlash = Vector2F::AddVector2F(downDir, Vector2F::MulVector2FFloat(rightDir, SPREAD_WIDTH));
	const Vector2F dirLeftSlash = Vector2F::AddVector2F(downDir, Vector2F::MulVector2FFloat(rightDir, -SPREAD_WIDTH));

	// 方向の決定
	const Vector2F DIR[CREATE_NUM] = {
		dirRightSlash,
		dirLeftSlash
	};

	for (int i = 0; i < CREATE_NUM; i++)
	{	
		std::unique_ptr<ParameterEffect> parameter = std::make_unique<ParameterEffect>();
		parameter->pos_ = parameter_.pos_;
		parameter->gravityDir_ = parameter_.gravityDir_;
		parameter->angle_ = std::atan2f(DIR[i].y, DIR[i].x);
		parameter->hitRadius_ = 16.0f * parameter_.scale_;
		parameter->resourceKey_ = "airslash";
		parameter->scale_ = parameter_.scale_;
		parameter->divisionNum_ = { 4, 1 };
		parameter->transparent_ = true;
		parameter->moveSpeed_ = 3.0f;
		parameter->attackPower_ = parameter_.attackPower_;
		parameter->attackBoostRate_ = parameter_.attackBoostRate_;
		parameter->componentkeys_ = { "spriteAnimation" };
		parameter->animationDataMap_.emplace("effect", Animation::Data(0, 3, 0.3));
		std::unique_ptr<EffectAirslash> effect = std::make_unique<EffectAirslash>(std::move(parameter), DIR[i]);
		SpriteEffectManager::GetInstance().Add(std::move(effect));
	}
}