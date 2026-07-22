#include "../../OnHit/OnHitItemBase.h"
#include "../../Collider/ColliderCircle.h"
#include "ItemPotion.h"

ItemPotion::ItemPotion(std::unique_ptr<ParameterItemPotion> parameter) :
	ItemBase(std::move(parameter))
{
	// パラメータ
	parameterItemPotion_ = dynamic_cast<ParameterItemPotion*>(GetParameterItemPtr());
	assert(parameterItemPotion_ != nullptr);
}

ItemPotion::~ItemPotion()
{
}

void ItemPotion::Init()
{
	// 衝突後処理
	onHit_ = std::make_unique<OnHitItemBase>(*this);

	// コライダー生成
	collider_ = std::make_shared<ColliderCircle>(*this, parameterItemPotion_->tag_, parameterItemPotion_->pos_, parameterItemPotion_->hitRadius_);

	// 基底クラスの処理
	ActorBase::Init();

	// 削除時間を設定
	deleteTimer_ = DELETE_TIME;
}