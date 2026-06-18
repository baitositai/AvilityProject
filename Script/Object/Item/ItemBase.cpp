#include <DxLib.h>
#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Common/Camera.h"
#include "../../Collider/ColliderCircle.h"
#include "../../OnHit/OnHitItemBase.h"
#include "ItemBase.h"

ItemBase::ItemBase(std::unique_ptr<ParameterItem> parameter) :
	ActorBase(std::move(parameter))
{
	// プレイヤー用のパラメータ
	parameterItem_ = dynamic_cast<ParameterItem*>(GetParameterActorPtr());
	assert(parameterItem_ != nullptr);

	// 初期化
	tag_ = CollisionTags::TAG::MAX;
	isCarryOver_ = false;
}

ItemBase::~ItemBase()
{
}

void ItemBase::Init()
{
	// 衝突後処理
	onHit_ = std::make_unique<OnHitItemBase>(*this);

	// コライダー生成
	collider_ = std::make_shared<ColliderCircle>(*this, tag_, parameterItem_->pos_, parameterItem_->hitRadius_);

	// 基底クラスの処理
	ActorBase::Init();
}

void ItemBase::Update()
{
	// 移動量を初期化
	parameterItem_->moveAmount_ = {};

	// 基底クラスの処理
	ActorBase::Update();
}

void ItemBase::Draw()
{
	// 描画位置を設定
	Vector2F cameraPos = mainCamera.GetPos();
	parameterItem_->drawPos_ = Vector2::AddVector2(Vector2::AddVector2(parameterItem_->pos_.ToVector2(), parameterItem_->localPos_), cameraPos.ToVector2());

	if (!isDraw_) return;

	// 描画
	DrawRotaGraph(
		parameterItem_->drawPos_.x,
		parameterItem_->drawPos_.y,
		parameterItem_->scale_,
		parameterItem_->angle_,
		parameterItem_->spriteTexture_[parameterItem_->spriteIndex_],
		parameterItem_->transparent_,
		parameterItem_->direction_
	);
}

void ItemBase::DebugDraw()
{
	collider_->DebugDraw();
}

const bool ItemBase::IsCarryOver() const
{
	return isCarryOver_;
}

void ItemBase::SetIsCarryOver(const bool isCarry)
{
	isCarryOver_ = isCarry;
}
