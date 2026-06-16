#include "ItemCoinBag.h"

ItemCoinBag::ItemCoinBag(std::unique_ptr<ParameterItemMoney> parameter) :
	ItemBase(std::move(parameter))
{
	// パラメータ
	parameterItemMoney_ = dynamic_cast<ParameterItemMoney*>(GetParameterItemPtr());
	assert(parameterItemMoney_ != nullptr);

	// タグ定義
	tag_ = CollisionTags::TAG::ITEM_MONEY;
}

ItemCoinBag::~ItemCoinBag()
{
}
