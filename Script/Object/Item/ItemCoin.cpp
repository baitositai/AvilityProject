#include "ItemCoin.h"

ItemCoin::ItemCoin(std::unique_ptr<ParameterItemMoney> parameter) :
	ItemBase(std::move(parameter))
{
	// パラメータ
	parameterItemMoney_ = dynamic_cast<ParameterItemMoney*>(GetParameterItemPtr());
	assert(parameterItemMoney_ != nullptr);

	// タグ定義
	tag_ = CollisionTags::TAG::ITEM_MONEY;
}

ItemCoin::~ItemCoin()
{
}