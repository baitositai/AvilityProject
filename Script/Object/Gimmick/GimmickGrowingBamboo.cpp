#include <DxLib.h>
#include "../../Manager/Common/SceneManager.h"
#include "../../Collider/ColliderBox.h"
#include "GimmickGrowingBamboo.h"

GimmickGrowingBamboo::GimmickGrowingBamboo(std::unique_ptr<ParameterGimmickGrowingBamboo> parameter) :
	GimmickBase(std::move(parameter))
{
	// パラメータ情報
	parameterBamboo_ = dynamic_cast<ParameterGimmickGrowingBamboo*>(GetParameterGimmickPtr());
	assert(parameterBamboo_ != nullptr);

	// 変数の初期化
	growingCount_ = -1;
	timer_ = 0.0f;
	growLength_ = 0.0f;
	update_ = nullptr;
}

GimmickGrowingBamboo::~GimmickGrowingBamboo()
{
}

void GimmickGrowingBamboo::Init()
{
	// 竹の成長分の長さ
	growLength_ = static_cast<float>(parameterBamboo_->hitSize_.y);

	// 埋まっている分上に押し出し
	//parameterBamboo_->pos_.y;

	// コライダー
	collider_ = std::make_shared<ColliderBox>(*this, CollisionTags::TAG::ENEMY_ATTACK_NORMAL, parameterBamboo_->pos_, parameterBamboo_->hitSize_, parameterBamboo_->angle_);
	
	// 基底クラスの初期化
	ActorBase::Init();

	// タイマー初期化
	timer_ = parameterBamboo_->growIntervalTime_;

	// 成長カウント設定
	growingCount_ = 1;

	// 初期更新処理
	update_ = std::bind(&GimmickGrowingBamboo::UpdateGrow, this);
}

void GimmickGrowingBamboo::Update()
{
	update_();
}

void GimmickGrowingBamboo::Draw()
{
	// 描画サイズを現在のスケールに合わせる
	Vector2 nowSize = Vector2F::MulVector2FFloat(parameterBamboo_->drawSize_.ToVector2F(), parameterBamboo_->scale_).ToVector2();

	// 中心位置に設定
	parameterBamboo_->drawPos_ = GetDrawCenterPos(nowSize);

	// 開始位置を調整
	parameterBamboo_->drawPos_.y += static_cast<float>(parameterBamboo_->hitSize_.y) / 2.0f - growLength_ / 2.0f;

	for (int i = 0; i < growingCount_; i++)
	{
		// 描画
		DrawRotaGraph(
			parameterBamboo_->drawPos_.x,
			parameterBamboo_->drawPos_.y - growLength_ * i,
			parameterBamboo_->scale_,
			parameterBamboo_->angle_,
			parameterBamboo_->texture_,
			parameterBamboo_->transparent_,
			parameterBamboo_->direction_
		);
	}
}

void GimmickGrowingBamboo::UpdateGrow()
{
	// タイマー
	timer_ -= scnMng_.GetDeltaTime();
	if (timer_ < 0.0f)
	{
		// タイマー初期化
		timer_ = GROWING_INTERVAL;

		// 竹の長さを伸ばす
		parameterBamboo_->hitSize_.y += growLength_;

		// 中心位置をずらす
		parameterBamboo_->pos_.y -= growLength_ / 2.0f;

		// 成長をカウント
		growingCount_++;

		// 一定回数成長した場合
		if (growingCount_ > parameterBamboo_->growCountMax_)
		{
			update_ = std::bind(&GimmickGrowingBamboo::UpdateWait, this);

			timer_ = parameterBamboo_->deleteWaitTime_;
			return;
		}
	}
}

void GimmickGrowingBamboo::UpdateWait()
{
	timer_ -= scnMng_.GetDeltaTime();
	if (timer_ < 0.0f)
	{
		Delete();
	}
}