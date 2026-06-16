#include "ItemTreasure.h"

ItemTreasure::ItemTreasure(std::unique_ptr<ParameterItemTreasure> parameter) :
	ItemBase(std::move(parameter))
{
	// パラメータ
	parameterItemTreasure_ = dynamic_cast<ParameterItemTreasure*>(GetParameterItemPtr());
	assert(parameterItemTreasure_ != nullptr);

	// タグ定義
	tag_ = CollisionTags::TAG::ITEM_TREASURE;
}

ItemTreasure::~ItemTreasure()
{
}
