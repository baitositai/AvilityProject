#include "EffectTargetFollow.h"

EffectTargetFollow::EffectTargetFollow(std::unique_ptr<ParameterEffect> parameter) :
	EffectBase(std::move(parameter))
{
	parameterEffect_ = GetParameterEffectPtr();
}

EffectTargetFollow::~EffectTargetFollow()
{
}

void EffectTargetFollow::Update()
{
	// 空,もしくは削除予定の場合
	if (!target_ || target_->IsDelete())
	{
		// 削除して終了
		Delete();
		return;
	}

	// 座標追従
	parameterEffect_->pos_ = Vector2F::AddVector2F(target_->GetParameter().pos_, parameterEffect_->localPos_.ToVector2F());

	// 基底クラスの処理
	ActorBase::Update();

	// ループ予定、またはアニメーションが続いている場合、終了
	if (parameterEffect_->isLoop_ || animation_->IsPlay()) return;

	// 削除処理
	Delete();
}

void EffectTargetFollow::SetTarget(const ActorBase* target)
{
	// ターゲット取得
	target_ = target;
}
