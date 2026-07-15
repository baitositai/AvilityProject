#include "ItemAvility.h"

#include "../../Manager/Common/ResourceManager.h"
#include "../../Manager/Common/SceneManager.h"
#include "../../Resource/ResourceTexture.h"
#include "../../Render/PixelMaterial.h"
#include "../../Render/PixelRenderer.h"
#include "../../Utility/UtilityCommon.h"

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

void ItemAvility::Draw()
{
	// 描画用の番号を付与
	parameterItem_->drawIndex_ = (float)parameterItem_->spriteIndex_;

	// 描画しない場合は無視
	if (!isDraw_) return;

	// 中心位置に設定
	GetParameter().drawPos_ = GetDrawPos(GetParameter().drawSize_);

	// メッシュ生成
	renderer_->MakeSquereVertex(GetParameter().drawPos_, GetParameter().drawSize_, GetParameter().angle_, GetParameter().scale_, GetParameter().direction_);

	// 定数バッファの更新
	material_->SetConstBuf(0, FLOAT4{ GetParameter().color_.x, GetParameter().color_.y ,GetParameter().color_.z,GetParameter().alpha_ });
	material_->SetConstBuf(1, FLOAT4{ (float)GetParameter().divisionNum_.x, (float)GetParameter().divisionNum_.y, GetParameter().drawIndex_
		, SceneManager::GetInstance().GetTotalTime() });

	// 描画処理
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)UtilityCommon::ALPHA_MAX);
	renderer_->Draw();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

const std::string ItemAvility::GetCreateAvilityName() const
{
	return AvilityTypes::AVILITY_NAME_MAP.at(parameterItemAvility_->type_);
}

const int ItemAvility::GetAvilityItemResourceIndex() const
{
	return parameterItemAvility_->spriteIndex_;
}

void ItemAvility::InitDraw()
{
	// リソースの取得と同時に必要な情報を取得
	const auto texture = resMng_.GetResourceTexture(GetParameter().resourceKey_);
	GetParameter().drawSize_ = texture->GetSize();
	GetParameter().divisionNum_ = texture->GetDivsion();
	GetParameter().drawHalfSize_ = Vector2(GetParameter().drawSize_.x / 2, GetParameter().drawSize_.y / 2);

	// 基底クラスではスプライト画像を前提で用意
	// マテリアルの生成
	material_ = std::make_unique<PixelMaterial>(resMng_.GetHandle("ItemSprite"), DEFAULT_CONST_BUFFER_SIZE);

	// テクスチャの設定
	material_->AddTextureBuf(GetParameter().texture_);

	// バッファーの設定
	material_->AddConstBuf(FLOAT4{ GetParameter().color_.x, GetParameter().color_.y,GetParameter().color_.z, GetParameter().alpha_ });
	material_->AddConstBuf(FLOAT4{ (float)GetParameter().divisionNum_.x, (float)GetParameter().divisionNum_.y, GetParameter().drawIndex_, 0.0f});

	// レンダラーの生成
	renderer_ = std::make_unique<PixelRenderer>(*material_);
}
