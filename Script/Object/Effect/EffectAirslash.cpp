#include "../../Manager/Common/SceneManager.h"
#include "../../Collider/ColliderCircle.h"
#include "../../OnHit/OnHitEffect.h"
#include "EffectAirslash.h"

EffectAirslash::EffectAirslash(std::unique_ptr<ParameterEffect> parameter, const Vector2F& direction) :
	DIRECTION(direction),
	EffectBase(std::move(parameter))
{
	time_ = 0.0f;
	parameterEffect_ = GetParameterEffectPtr();

	// コライダー
	collider_ = std::make_shared<ColliderCircle>(*this, CollisionTags::TAG::AIRSLASH, parameterEffect_->pos_, parameterEffect_->hitRadius_);

	// 衝突後処理
	onHit_ = std::make_unique<OnHitEffect>(*this);
}

EffectAirslash::~EffectAirslash()
{
}

void EffectAirslash::Init()
{
	// 基底クラスの初期化
	ActorBase::Init();

	// 再生
	animation_->Play(Animation::TYPE::EFFECT);
}

void EffectAirslash::Update()
{
	// 削除用カウント処理
	time_ += scnMng_.GetDeltaTime();
	if (time_ >= ALIVE_TIME)
	{
		Delete();
	}

	// 移動量の更新
	parameterEffect_->pos_ = Vector2F::AddVector2F(
		parameterEffect_->pos_, 
		Vector2F::MulVector2FFloat(DIRECTION, parameterEffect_->moveSpeed_));

	// 基底クラスの処理
	ActorBase::Update();
}