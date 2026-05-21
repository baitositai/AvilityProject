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
	abilitySlot_ = ABILITY_SLOT::SECOND;
	type_ = AvilityTypes::TYPE::AIRSLASH;
	preJumpCount_ = parameter_.jumpCount_;
	parameter_.attackPower_ += 0;
}

ComponentAvilityAirslash::~ComponentAvilityAirslash()
{
}

void ComponentAvilityAirslash::Update()
{
	// ジャンプ回数の比較
	const int nowJumpCount = parameter_.jumpCount_;
	if (preJumpCount_ > nowJumpCount)
	{
		CreateAirslash();
	}
	
	// バックアップ保持
	preJumpCount_ = nowJumpCount;
}

void ComponentAvilityAirslash::Remove()
{
	parameter_.attackPower_ -= 50;
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
		parameter->hitRadius_ = 16.0f;
		parameter->resourceKey_ = "airslash";
		parameter->scale_ = 1.0f;
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