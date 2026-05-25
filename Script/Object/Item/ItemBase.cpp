#include "../Collider/ColliderBase.h"
#include "../../Object/Common/Animation.h"
#include "ItemBase.h"

ItemBase::ItemBase(std::unique_ptr<ParameterItem> parameter) :
	ActorBase(std::move(parameter))
{
	// プレイヤー用のパラメータ
	parameterItem_ = dynamic_cast<ParameterItem*>(GetParameterActorPtr());
	assert(parameterItem_ != nullptr);
}

ItemBase::~ItemBase()
{
}

void ItemBase::DebugDraw()
{
	collider_->DebugDraw();
}
