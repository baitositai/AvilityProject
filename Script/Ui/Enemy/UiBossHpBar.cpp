#include <DxLib.h>
#include "../../Application.h"
#include "../../Object/Character/Enemy/EnemyBoss.h"
#include "../../Manager/Common/ResourceManager.h"
#include "UiBossHpBar.h"

UiBossHpBar::UiBossHpBar(EnemyBoss& owner) :
	owner_(owner)
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

UiBossHpBar::~UiBossHpBar()
{
}

void UiBossHpBar::Init()
{
	// リソースの設定
	handle_ = resourceManager_.GetHandle("hpGageBoss");
	hpBarHandles_ = resourceManager_.GetHandles("hpBars");

	// HPゲージの設定
	pos_ = { Application::SCREEN_HALF_X, 150 };

	// HPバーの設定
	Vector2 localPos = { 0, 2 };
	hpBarPos_ = Vector2::AddVector2(pos_, localPos);
	hpBarSize_ = { 700, 27 };
	hpBarLength_ = hpBarSize_.x;
	hpBarPos_.x -= hpBarSize_.x / 2;

	// ネームプレートの設定
	namePlateHandle_ = resourceManager_.GetHandles("bossNamePlate")[owner_.GetParameter().bossUiNamePlateIndex_];
	namePlatePos_ = pos_;
	namePlatePos_.x -= (hpBarSize_.x / 2 - 150);
	namePlatePos_.y -= 35;

	// 前HP
	preHp_ = owner_.GetParameter().hp_;
}

void UiBossHpBar::Update()
{
	if (owner_.IsDelete())
	{
		Delete();
		return;
	}

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

void UiBossHpBar::Draw()
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

		DrawRotaGraph(
			namePlatePos_.x,
			namePlatePos_.y,
			scale_,
			angle_,
			namePlateHandle_,
			true
		);
	}
}

void UiBossHpBar::UpdateDamageBar()
{
	specialHpBarLength_ -= HPBAR_MOVE_SPEED;
	if (hpBarLength_ >= (int)specialHpBarLength_)
	{
		specialHpBarLength_ = hpBarLength_;
		updateHpBar_ = nullptr;
	}
}

void UiBossHpBar::UpdateHealBar()
{
	specialHpBarLength_ += HPBAR_MOVE_SPEED;
	if (hpBarLength_ <= (int)specialHpBarLength_)
	{
		specialHpBarLength_ = hpBarLength_;
		updateHpBar_ = nullptr;
	}
}

void UiBossHpBar::ChangeDamageBar()
{
	updateHpBar_ = std::bind(&UiBossHpBar::UpdateDamageBar, this);
	specialHpBarIndex_ = HPBAR_DAMAGE;
}

void UiBossHpBar::ChangeHealBar()
{
	updateHpBar_ = std::bind(&UiBossHpBar::UpdateHealBar, this);
	specialHpBarIndex_ = HPBAR_HEAL;
}
