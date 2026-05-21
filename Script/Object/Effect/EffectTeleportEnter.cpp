#include "../Common/Animation.h"
#include "EffectTeleportEnter.h"

EffectTeleportEnter::EffectTeleportEnter(std::unique_ptr<ParameterEffect> parameter) :
	EffectBase(std::move(parameter))
{
	parameterEffectTeleportEnter_ = GetParameterEffectPtr();
}

EffectTeleportEnter::~EffectTeleportEnter()
{
}

void EffectTeleportEnter::Update()
{
	// 基底クラスの処理
	ActorBase::Update();

	// アニメーションが終了したら消す
	if (animation_->IsPlay()) return;
	Delete();
}
