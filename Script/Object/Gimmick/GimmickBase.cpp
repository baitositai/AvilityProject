#include <DxLib.h>
#include "../../Manager/Common/ResourceManager.h"
#include "../../Render/PixelMaterial.h"
#include "../../Render/PixelRenderer.h"
#include "../Common/Animation.h"
#include "GimmickBase.h"

GimmickBase::GimmickBase(std::unique_ptr<ParameterGimmick> parameter) :
	ActorBase(std::move(parameter))
{
	gimmickType_ = TYPE::MAX;

	// パラメータ
	parameterGimmick_ = dynamic_cast<ParameterGimmick*>(GetParameterActorPtr());
	assert(parameterGimmick_ != nullptr);
}

GimmickBase::~GimmickBase()
{
}

void GimmickBase::Init(void)
{
	ActorBase::Init();
}

void GimmickBase::InitResource()
{
	// リソースに指定がない場合無視
	if (parameterGimmick_->resourceKey_ == "")
	{
		return;
	}

	// リソース取得
	parameterGimmick_->texture_ = resMng_.GetHandle(parameterGimmick_->resourceKey_);
}

void GimmickBase::Update(void)
{
	ActorBase::Update();
}

void GimmickBase::Draw(void)
{
	// 描画しない場合は無視
	if (!isDraw_) return;

	// 描画位置を取得
	parameterGimmick_->drawPos_ = GetDrawCenterPos();

	// 描画サイズを現在のスケールに合わせる
	Vector2F nowSize = Vector2F::MulVector2FFloat(parameterGimmick_->drawSize_.ToVector2F(), parameterGimmick_->scale_);

	// メッシュ生成
	renderer_->MakeSquereVertex(parameterGimmick_->drawPos_, nowSize.ToVector2());

	// X軸の反転
	float isReverseX = parameterGimmick_->direction_ ? 1.0f : 0.0f;

	// 定数バッファの更新
	material_->SetConstBuf(0, FLOAT4{ parameterGimmick_->color_.x,parameterGimmick_->color_.y ,parameterGimmick_->color_.z, parameterGimmick_->alpha_ });
	material_->SetConstBuf(1, FLOAT4{ isReverseX, 0.0f, parameterGimmick_->scale_, parameterGimmick_->angle_ });

	// 描画処理
	renderer_->Draw();
}

void GimmickBase::DebugDraw(void)
{
	ActorBase::DebugDraw();
}

void GimmickBase::InitDraw()
{
	// リソースの取得と同時に必要な情報を取得
	parameterGimmick_->drawSize_ = parameterGimmick_->hitSize_;
	parameterGimmick_->drawHalfSize_ = Vector2(parameterGimmick_->drawSize_.x / 2, parameterGimmick_->drawSize_.y / 2);

	// X軸の反転
	float isReverseX = parameterGimmick_->direction_ ? 1.0f : 0.0f;

	// 基底クラスではスプライト画像を前提で用意
	// マテリアルの生成
	material_ = std::make_unique<PixelMaterial>(resMng_.GetHandle("standardTexture"), CONST_BUFFER_SIZE);
	material_->AddTextureBuf(parameterGimmick_->texture_);
	material_->AddConstBuf(FLOAT4{ parameterGimmick_->color_.x, parameterGimmick_->color_.y,parameterGimmick_->color_.z, parameterGimmick_->alpha_ });
	material_->AddConstBuf(FLOAT4{ isReverseX, 0.0f, parameterGimmick_->scale_, parameterGimmick_->angle_ });

	// レンダラーの生成
	renderer_ = std::make_unique<PixelRenderer>(*material_);

	// 中心位置に設定
	parameterGimmick_->drawPos_ = GetDrawCenterPos();

	// 描画サイズを現在のスケールに合わせる
	Vector2F nowSize = Vector2F::MulVector2FFloat(parameterGimmick_->drawSize_.ToVector2F(), parameterGimmick_->scale_);

	// メッシュ生成
	renderer_->MakeSquereVertex(parameterGimmick_->drawPos_, nowSize.ToVector2());
}