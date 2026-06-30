#include <DxLib.h>
#include "../../Application.h"
#include "../../Object/Character/Enemy/EnemyBase.h"
#include "../../Manager/Common/ResourceManager.h"
#include "UiBossHpBar.h"

UiBossHpBar::UiBossHpBar(EnemyBase& owner) :
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
	pos_ = { Application::SCREEN_HALF_X, 200 };

	// HPバーの設定
	Vector2 localPos = { 0, 20 };
	hpBarPos_ = Vector2::AddVector2(pos_, localPos);
	hpBarSize_ = { 166, 21 };
	hpBarLength_ = hpBarSize_.x;
	hpBarPos_.x -= hpBarSize_.x / 2;

	// 前HP
	preHp_ = owner_.GetParameter().hp_;
}

void UiBossHpBar::Update()
{
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

//void UiBossHpBar::UpdateHealBar()
//{
//	specialHpBarLength_ += HPBAR_MOVE_SPEED;
//	if (hpBarLength_ <= (int)specialHpBarLength_)
//	{
//		specialHpBarLength_ = hpBarLength_;
//		updateHpBar_ = nullptr;
//	}
//}

void UiBossHpBar::ChangeDamageBar()
{
	updateHpBar_ = std::bind(&UiBossHpBar::UpdateDamageBar, this);
	specialHpBarIndex_ = HPBAR_DAMAGE;
}

//void UiBossHpBar::ChangeHealBar()
//{
//	updateHpBar_ = std::bind(&UiBossHpBar::UpdateHealBar, this);
//	specialHpBarIndex_ = HPBAR_HEAL;
//}
