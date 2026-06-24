#include "../Object/ActorBase.h"
#include "ColliderBase.h"

ColliderBase::ColliderBase(ActorBase& owner, const CollisionTags::TAG tag, Vector2F& followPos) :
	owner_(owner),
	tag_(tag),
	followPos_(followPos)
{
	partnerTag_ = CollisionTags::TAG::NONE;
	type_ = ColliderType::TYPE::MAX;
	isHit_ = false;
	isDelete_ = false;
	isActive_ = true;
	isRegister_ = false;
	hitPos_ = {};
}

ColliderBase::~ColliderBase()
{
}

void ColliderBase::OnHit(const std::weak_ptr<ColliderBase>& opponentCollider)
{
	// 所有者のインスタンスを渡す
	owner_.OnHit(opponentCollider);
}

const bool ColliderBase::IsSkip() const
{
	if (isDelete_ ||			// コライダーが削除予定
		!isActive_ ||			// コライダーが非活動状態
		owner_.IsDelete() ||	// 所有者が削除予定
		!owner_.IsActive())		// 所有者が非活動状態
	{
		return true;	// スキップ
	}
	else
	{
		return false;	// 実行
	}
}

void ColliderBase::Delete()
{
	isActive_ = false;
	isDelete_ = true;
}

void ColliderBase::DebugDraw()
{
}
