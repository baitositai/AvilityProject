#include "../../Object/Common/Animation.h"
#include "../../OnHit/OnHitItem.h"
#include "../../Collider/ColliderCircle.h"
#include "ItemAvility.h"

ItemAvility::ItemAvility(Parameter& parameter, const std::vector<std::string>& componentNameList) :
	parameter_(parameter),
	ItemBase(&parameter_, componentNameList)
{
	// コライダー
	collider_ = std::make_shared<ColliderCircle>(*this, CollisionTags::TAG::ITEM_AVILITY, parameter_.pos, parameter_.hitRadius);

	// 衝突後処理
	onHit_ = std::make_unique<OnHitItem>(*this);
}

ItemAvility::~ItemAvility()
{
}
