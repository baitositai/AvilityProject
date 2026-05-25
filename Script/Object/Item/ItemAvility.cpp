#include "../Manager/Game/CollisionManager.h"
#include "../../Object/Common/Animation.h"
#include "../../OnHit/OnHitItem.h"
#include "../../Collider/ColliderCircle.h"
#include "ItemAvility.h"

ItemAvility::ItemAvility(std::unique_ptr<ParameterItemAvility> parameter) :
	ItemBase(std::move(parameter))
{
	// パラメータ
	parameterItemAvility_ = dynamic_cast<ParameterItemAvility*>(GetParameterCharacterPtr());
	assert(parameterItemAvility_ != nullptr);

	// コライダー
	collider_ = std::make_shared<ColliderCircle>(*this, CollisionTags::TAG::ITEM_AVILITY, parameterItemAvility_->pos_, parameterItemAvility_->hitRadius_);

	// 衝突後処理
	onHit_ = std::make_unique<OnHitItem>(*this);
}

ItemAvility::~ItemAvility()
{
}

const std::string ItemAvility::GetCreateAvilityName() const
{
	return AvilityTypes::AVILITY_NAME_MAP.at(parameterItemAvility_->type_);
}