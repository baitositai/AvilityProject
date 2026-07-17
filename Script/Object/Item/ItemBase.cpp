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
	deleteTimer_ = 0.0f;
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

	// 削除時間を設定
	deleteTimer_ = DELETE_TIME;
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

	// 点滅処理
	if (deleteTimer_ < BLINK_START_TIME)
	{
		// 点滅の1周期にかかる時間
		constexpr int BLINK_CYCLE_MS = 200;

		// 現在の時間を取得
		int nowTime = GetNowCount();

		// 周期に基づいて角度を計算
		float currentAngle = (nowTime % BLINK_CYCLE_MS) * DX_PI_F * 2.0f / static_cast<float>(BLINK_CYCLE_MS);

		// 透過値の決定
		float alphaValue = (sin(currentAngle) + 1.0f) * 0.5f;

		// シェーダに渡すアルファ値を一時的に上書きして点滅
		float backupAlpha = parameterItem_->alpha_;
		parameterItem_->alpha_ = alphaValue;

		// 描画処理
		ActorBase::Draw();

		// 描画が終わったら元のアルファ値に戻す
		parameterItem_->alpha_ = backupAlpha;
	}
	else
	{
		// 描画処理
		ActorBase::Draw();
	}
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

void ItemBase::CountDeleteTime()
{
	// 持ち越す場合無視
	if (isCarryOver_) return;

	// タイマーカウント
	deleteTimer_ -= scnMng_.GetDeltaTime();
	if (deleteTimer_ < 0.0f)
	{
		isDelete_ = true;
	}
}
