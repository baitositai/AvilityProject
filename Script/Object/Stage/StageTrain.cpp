#include "../../Manager/Game/CollisionManager.h"
#include "../../Collider/ColliderBox.h"
#include "StageTrain.h"


StageTrain::StageTrain(std::unique_ptr<ParameterStage> parameter) :
	Stage(std::move(parameter))
{
	// パラメータ
	parameterStageTrain_ = GetParameterStagePtr();

	// コライダー
	parameterStageTrain_->pos_ = parameterStageTrain_->localPos_.ToVector2F();
	colliderBox_ = std::make_unique<ColliderBox>(*this, CollisionTags::TAG::CHANGE_NEXT_AREA, parameterStageTrain_->pos_, parameterStageTrain_->hitSize_, parameterStageTrain_->angle_);
	collMng_.Add(colliderBox_);
}

StageTrain::~StageTrain()
{
}
