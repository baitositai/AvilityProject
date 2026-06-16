#include "ItemFood.h"

ItemFood::ItemFood(std::unique_ptr<ParameterItemFood> parameter) :
	ItemBase(std::move(parameter))
{
	// パラメータ
	parameterItemFood_ = dynamic_cast<ParameterItemFood*>(GetParameterItemPtr());
	assert(parameterItemFood_ != nullptr);

	// タグ定義
	tag_ = CollisionTags::TAG::ITEM_FOOD;
}

ItemFood::~ItemFood()
{
}
