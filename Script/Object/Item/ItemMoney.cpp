#include "../../Collider/ColliderCircle.h"
#include "../../OnHit/OnHitItemMoney.h"
#include "../Common/Animation.h"
#include "ItemMoney.h"

ItemMoney::ItemMoney(std::unique_ptr<ParameterItemMoney> parameter) :
	ItemBase(std::move(parameter))
{
	// パラメータ
	parameterItemMoney_ = dynamic_cast<ParameterItemMoney*>(GetParameterItemPtr());
	assert(parameterItemMoney_ != nullptr);

	// タグ定義
	tag_ = CollisionTags::TAG::ITEM_MONEY;
}

ItemMoney::~ItemMoney()
{
}

void ItemMoney::Init()
{
	// 衝突後処理
	onHit_ = std::make_unique<OnHitItemMoney>(*this);

	// コライダー生成
	collider_ = std::make_shared<ColliderCircle>(*this, tag_, parameterItemMoney_->pos_, parameterItemMoney_->hitRadius_);

	// 基底クラスの処理
	ActorBase::Init();

	animation_->Play(Animation::TYPE::IDLE);

	// 削除時間を設定
	deleteTimer_ = DELETE_TIME;
}

void ItemMoney::Draw()
{
	ActorBase::Draw();
}
