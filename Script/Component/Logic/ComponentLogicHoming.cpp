#include "../../Object/Character/Enemy/EnemyAzagrim.h"
#include "../../Object/Effect/EffectHoming.h"
#include "ComponentLogicHoming.h"

ComponentLogicHoming::ComponentLogicHoming(EnemyAzagrim& owner):
	ComponentLogicBase(owner),
	owner_(owner)
{
}

ComponentLogicHoming::~ComponentLogicHoming()
{
}

void ComponentLogicHoming::Create()
{
}

void ComponentLogicHoming::Init()
{
	ComponentLogicBase::Init();
}

void ComponentLogicHoming::Update()
{
	owner_.MobiusLoop();
}

void ComponentLogicHoming::CreateHomingEffect()
{
	std::unique_ptr<ParameterEffect> parameter = std::make_unique<ParameterEffect>();
	parameter->pos_ = parameter_.pos_;
	parameter->gravityDir_ = parameter_.gravityDir_;
	parameter->angle_ = std::atan2f(dir.y, dir.x);
	parameter->hitRadius_ = 16.0f * parameter_.scale_;
	parameter->resourceKey_ = "airslash";
	parameter->scale_ = parameter_.scale_;
	parameter->divisionNum_ = { 4, 1 };
	parameter->transparent_ = true;
	parameter->moveSpeed_ = 10.0f;
	parameter->attackPower_ = parameter_.attackPower_;
	parameter->attackBoostRate_ = parameter_.attackBoostRate_;
	parameter->componentkeys_ = { "spriteAnimation" };
	parameter->tag_ = CollisionTags::TAG::ENEMY_ATTACK_NORMAL;
	parameter->color_ = VECTOR{ 1.0f, 0.1f, 1.5f };
	parameter->animationDataMap_.emplace("effect", Animation::Data(0, 3, 0.3));
	std::unique_ptr<EffectAirslash> effect = std::make_unique<EffectAirslash>(std::move(parameter), dir);
	spriteEffectManager_.Add(std::move(effect));
}
