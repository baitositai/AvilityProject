#include "../../Object/Common/Animation.h"
#include "ItemBase.h"

ItemBase::ItemBase(Parameter* parameter, const std::vector<std::string>& componentNameList, std::unique_ptr<Animation> animation) :
	ActorBase(parameter, componentNameList, std::move(animation))
{
}

ItemBase::~ItemBase()
{
}
