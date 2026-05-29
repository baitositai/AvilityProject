#include "../../Parameter/Gimmick/ParameterGimmick.h"
#include "../../Collider/ColliderBox.h"
#include "GimmickDoor.h"

GimmickDoor::GimmickDoor(std::unique_ptr<ParameterGimmick> parameter) :
	GimmickBase(std::move(parameter))
{
	// パラメータ
	parameterDoor_ = GetParameterGimmickPtr();
	gimmickType_ = TYPE::DOOR;

	// コライダー
	collider_ = std::make_unique<ColliderBox>(*this, CollisionTags::TAG::DOOR, parameterDoor_->pos_, parameterDoor_->hitSize_, parameterDoor_->angle_);
}

GimmickDoor::~GimmickDoor()
{
}
