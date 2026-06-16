#include "ItemAvility.h"

ItemAvility::ItemAvility(std::unique_ptr<ParameterItemAvility> parameter) :
	ItemBase(std::move(parameter))
{
	// パラメータ
	parameterItemAvility_ = dynamic_cast<ParameterItemAvility*>(GetParameterItemPtr());
	assert(parameterItemAvility_ != nullptr);

	// タグ定義
	tag_ = CollisionTags::TAG::ITEM_AVILITY;
}

ItemAvility::~ItemAvility()
{
}

const std::string ItemAvility::GetCreateAvilityName() const
{
	return AvilityTypes::AVILITY_NAME_MAP.at(parameterItemAvility_->type_);
}