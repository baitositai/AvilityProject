#include <DxLib.h>
#include "../../Object/Character/Player.h"
#include "../../Manager/Common/ResourceManager.h"
#include "UiPlayerHpBar.h"

UiPlayerHpBar::UiPlayerHpBar(const Player& owner) :
	UiPlayerBase(owner)
{
	hpBarPos_ = {};
	hpBarSize_ = {};
	preHp_ = -1;
	specialHpBarIndex_ = -1;
	hpBarLength_ = -1;
	specialHpBarLength_ = 0.0f;
	hpBarHandles_ = nullptr;
	updateHpBar_ = nullptr;
}

UiPlayerHpBar::~UiPlayerHpBar()
{
}

void UiPlayerHpBar::Init()
{
	UiPlayerBase::Init();

	// リソースの設定
	handle_ = resourceManager_.GetHandle("playerHpGage");
	hpBarHandles_ = resourceManager_.GetHandles("hpBars");

	// HPゲージの設定
	Vector2 localPos = { -34, 18 };
	pos_ = Vector2::AddVector2(basePos_, localPos);

	// HPバーの設定
	localPos = { -34, 20 };
	hpBarPos_ = Vector2::AddVector2(basePos_, localPos);
	hpBarSize_ = { 166, 21 };
	hpBarLength_ = hpBarSize_.x;
	hpBarPos_.x -= hpBarSize_.x / 2;

	// 前HP
	preHp_ = owner_.GetParameter().hp_;
}

void UiPlayerHpBar::Update()
{
	if (CheckOwnerDead()) { return; }

	// パラメータ取得
	auto& parameter = owner_.GetParameter();

	// 1HP分の長さ
	const float lengthByOneHp = static_cast<float>(hpBarSize_.x) / static_cast<float>(parameter.hpMax_);

	// 現在HPが最大HPより大きい場合
	if (parameter.hp_ >= parameter.hpMax_)
	{
		// 最大長さを設定
		hpBarLength_ = hpBarSize_.x;
	}
	// 小さい場合
	else
	{
		// 更新
		hpBarLength_ = static_cast<int>(lengthByOneHp * static_cast<float>(parameter.hp_));
	}
	// 特別なHPバーの更新
	if (updateHpBar_)
	{
		updateHpBar_();
	}

	// 前フレームのHPと異なる場合
	if (preHp_ != parameter.hp_)
	{
		// HPの増減の違いから変更処理
		preHp_ < parameter.hp_ ? ChangeHealBar() : ChangeDamageBar();

		// 特別なHPバーの長さを決める
		specialHpBarLength_ = static_cast<int>(lengthByOneHp * static_cast<float>(preHp_));

		// 現在のHPをバックアップ
		preHp_ = parameter.hp_;
	}
}

void UiPlayerHpBar::Draw()
{
	if (isActive_)
	{
		DrawRotaGraph(
			pos_.x,
			pos_.y,
			scale_,
			angle_,
			handle_,
			true
		);

		DrawExtendGraph(
			hpBarPos_.x,
			hpBarPos_.y - hpBarSize_.y / 2,
			hpBarPos_.x + hpBarLength_,
			hpBarPos_.y + hpBarSize_.y / 2,
			hpBarHandles_[HPBAR_NORMAL],
			true
		);

		if (updateHpBar_)
		{
			// どちらのバーが右側に来るかを判定して左右の座標を正しく設定する
			float leftX = hpBarPos_.x + hpBarLength_;
			float rightX = hpBarPos_.x + specialHpBarLength_;

			if (leftX > rightX)
			{
				float temp = leftX;
				leftX = rightX;
				rightX = temp;
			}

			DrawExtendGraph(
				leftX,
				hpBarPos_.y - hpBarSize_.y / 2,
				rightX,
				hpBarPos_.y + hpBarSize_.y / 2,
				hpBarHandles_[specialHpBarIndex_],
				true
			);
		}
	}
}

void UiPlayerHpBar::UpdateDamageBar()
{
	specialHpBarLength_ -= HPBAR_MOVE_SPEED;
	if (hpBarLength_ >= (int)specialHpBarLength_)
	{
		specialHpBarLength_ = hpBarLength_;
		updateHpBar_ = nullptr;
	}
}

void UiPlayerHpBar::UpdateHealBar()
{
	specialHpBarLength_ += HPBAR_MOVE_SPEED;
	if (hpBarLength_ <= (int)specialHpBarLength_)
	{
		specialHpBarLength_ = hpBarLength_;
		updateHpBar_ = nullptr;
	}
}

void UiPlayerHpBar::ChangeDamageBar()
{
	updateHpBar_ = std::bind(&UiPlayerHpBar::UpdateDamageBar, this);
	specialHpBarIndex_ = HPBAR_DAMAGE;
}

void UiPlayerHpBar::ChangeHealBar()
{
	updateHpBar_ = std::bind(&UiPlayerHpBar::UpdateHealBar, this);
	specialHpBarIndex_ = HPBAR_HEAL;
}
