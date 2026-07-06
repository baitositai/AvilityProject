#include <DxLib.h>
#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Common/ResourceManager.h"
#include "../../Manager/Common/Camera.h"
#include "../../Render/PixelMaterial.h"
#include "../../Render/PixelRenderer.h"
#include "../../Resource/ResourceTexture.h"
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
	// 描画用の番号を付与
	parameterItem_->drawIndex_ = (float)parameterItem_->spriteIndex_;

	// 基底クラスの描画
	ActorBase::Draw();
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

void ItemBase::InitDraw()
{
	// リソースの取得と同時に必要な情報を取得
	const auto texture = resMng_.GetResourceTexture(parameterItem_->resourceKey_);
	parameterItem_->drawSize_ = texture->GetSize();
	parameterItem_->divisionNum_ = texture->GetDivsion();
	parameterItem_->drawHalfSize_ = Vector2(parameterItem_->drawSize_.x / 2, parameterItem_->drawSize_.y / 2);

	// X軸の反転
	float isReverseX = parameterItem_->direction_ ? 1.0f : 0.0f;

	// 基底クラスではスプライト画像を前提で用意
	// マテリアルの生成
	material_ = std::make_unique<PixelMaterial>(resMng_.GetHandle("standardSprite"), DEFAULT_CONST_BUFFER_SIZE);
	material_->AddTextureBuf(resMng_.GetHandle(parameterItem_->resourceKey_));
	material_->AddConstBuf(FLOAT4{ parameterItem_->color_.x, parameterItem_->color_.y,parameterItem_->color_.z, parameterItem_->alpha_ });
	material_->AddConstBuf(FLOAT4{ isReverseX, 0.0f, parameterItem_->scale_, parameterItem_->angle_ });
	material_->AddConstBuf(FLOAT4{ (float)parameterItem_->divisionNum_.x, (float)parameterItem_->divisionNum_.y,0.0f, 0.0f });

	// レンダラーの生成
	renderer_ = std::make_unique<PixelRenderer>(*material_);

	// 描画サイズを現在のスケールに合わせる
	Vector2 nowSize = Vector2F::MulVector2FFloat(parameterItem_->drawSize_.ToVector2F(), parameterItem_->scale_).ToVector2();

	// 中心位置に設定
	parameterItem_->drawPos_ = GetDrawCenterPos(nowSize);

	// メッシュ生成
	renderer_->MakeSquereVertex(parameterItem_->drawPos_, nowSize);
}
