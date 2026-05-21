#include "../../Collider/ColliderBox.h"
#include "../../OnHit/OnHitEffect.h"
#include "EffectTeleportExit.h"

EffectTeleportExit::EffectTeleportExit(std::unique_ptr<ParameterEffectTeleportExit> parameter) :
	EffectBase(std::move(parameter))
{
	// パラメータ情報
	parameterEffectTeleportExit_ = dynamic_cast<ParameterEffectTeleportExit*>(GetParameterEffectPtr());
	assert(parameterEffectTeleportExit_ != nullptr);

	// 衝突後処理
	//onHit_ = std::make_unique<OnHitEffect>(*this);
	
	// コライダー
	collider_ = std::make_unique<ColliderBox>(*this, CollisionTags::TAG::TELEPORT_EXIT,parameterEffectTeleportExit_->pos_, parameterEffectTeleportExit_->hitSize_, parameterEffectTeleportExit_->angle_);
}

EffectTeleportExit::~EffectTeleportExit()
{
}

void EffectTeleportExit::Update()
{
	// アニメーション番号が指定の番号以上になったら
	if (animation_->GetAnimationIndex() >= 4)
	{
		collider_->SetIsActive(true);
	}

	// 基底クラスの処理
	ActorBase::Update();

	// アニメーションが終了したら消す
	if (animation_->IsPlay()) return;
	Delete();
}
