#include "../../Collider/ColliderBox.h"
#include "GimmickShop.h"

GimmickShop::GimmickShop(std::unique_ptr<ParameterGimmick> parameter) :
	GimmickBase(std::move(parameter))
{
	// パラメータ情報
	parameterShop_ = GetParameterGimmickPtr();
}

GimmickShop::~GimmickShop()
{
}

void GimmickShop::Init()
{
	// コライダー
	collider_ = std::make_shared<ColliderBox>(*this, CollisionTags::TAG::SHOP, parameterShop_->pos_, parameterShop_->hitSize_, parameterShop_->angle_);

	// 基底クラスの処理
	GimmickBase::Init();
}