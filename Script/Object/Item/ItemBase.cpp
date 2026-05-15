#include "../Collider/ColliderBase.h"
#include "../../Object/Common/Animation.h"
#include "ItemBase.h"

ItemBase::ItemBase(Parameter* parameter, const std::vector<std::string>& componentNameList, std::unique_ptr<Animation> animation) :
	ActorBase(parameter, componentNameList, std::move(animation)),
	itemParameterPtr_(parameter)
{
}

ItemBase::~ItemBase()
{
}

void ItemBase::DebugDraw()
{
	collider_->DebugDraw();
}
