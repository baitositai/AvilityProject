#include <DxLib.h>
#include "../Utility/UtilityCommon.h"
#include "ColliderArray.h"

ColliderArray::ColliderArray(ActorBase& owner, const CollisionTags::TAG tag, const std::vector<std::vector<int>>& arrayOfArrays, const std::vector<int>& hitIds, const Vector2& chipSize) :
	ColliderBase(owner, tag),
	arrayOfArrays_(arrayOfArrays),
	hitIds_(hitIds),
	chipSize_(chipSize)
{	
	type_ = ColliderType::TYPE::ARRAY;
	result_ = {};
}

ColliderArray::~ColliderArray()
{
}

void ColliderArray::ResetResult()
{
	result_ = {};
}

void ColliderArray::DebugDraw()
{
}

std::shared_ptr<ColliderBase> ColliderArray::Clone() const
{
	return std::make_shared<ColliderArray>(*this);
}