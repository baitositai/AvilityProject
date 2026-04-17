#include "ColliderArray.h"

ColliderArray::ColliderArray(ActorBase& owner, const CollisionTags::TAG tag, const std::vector<std::vector<int>>& arrayOfArrays, const std::vector<int>& hitIds) :
	ColliderBase(owner, tag),
	arrayOfArrays_(arrayOfArrays),
	hitIds_(hitIds)
{
	result_ = {};
}

ColliderArray::~ColliderArray()
{
}