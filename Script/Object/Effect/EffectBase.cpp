#include "../Collider/ColliderBase.h"
#include "../Common/Animation.h"
#include "EffectBase.h"

EffectBase::EffectBase(std::unique_ptr<ParameterEffect> parameter) :
	 ActorBase(std::move(parameter))
{
	// パラメータ
	parameterEffect_ = dynamic_cast<ParameterEffect*>(GetParameterActorPtr());
	assert(parameterEffect_ != nullptr);
}

EffectBase::~EffectBase()
{
}

void EffectBase::Init()
{
	// 基底クラスの初期化
	ActorBase::Init();

	// 再生
	animation_->Play(Animation::TYPE::EFFECT, false);
}

void EffectBase::Draw()
{
	// アニメーション番号の指定
	parameterEffect_->drawIndex_ = animation_->GetAnimationIndex();

	// 基底クラスの処理
	ActorBase::Draw();
}

void EffectBase::DebugDraw()
{
	if (collider_)
	{
		collider_->DebugDraw();
	}
}