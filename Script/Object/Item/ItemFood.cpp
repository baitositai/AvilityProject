#include <math.h>
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

void ItemFood::Init()
{
	// 基底クラスの初期化処理
	ItemBase::Init();

	// 角度を重力に合わせる
	Vector2F gravityDir = GetParameter().GetGravityDirectionVector();
	parameterItemFood_->angle_ = atan2f(gravityDir.y, gravityDir.x);
}
