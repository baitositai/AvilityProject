#include "../../Collider/ColliderCircle.h"
#include "../../OnHit/OnHitTarget.h"
#include "GimmickTarget.h"

GimmickTarget::GimmickTarget(std::unique_ptr<ParameterGimmickTarget> parameter) :
	GimmickBase(std::move(parameter))
{
	// パラメータ情報
	parameterTarget_ = dynamic_cast<ParameterGimmickTarget*>(GetParameterGimmickPtr());
	assert(parameterTarget_ != nullptr);
}

GimmickTarget::~GimmickTarget()
{
}

void GimmickTarget::Init()
{
	// コライダー
	collider_ = std::make_unique<ColliderCircle>(*this, CollisionTags::TAG::TARGET, parameterTarget_->pos_, parameterTarget_->hitRadius_);

	// 衝突後処理
	onHit_ = std::make_unique<OnHitTarget>(*this);

	// 基底クラスの処理
	ActorBase::Init();
}

void GimmickTarget::Update()
{
	// 基底クラスの処理
	ActorBase::Update();
}