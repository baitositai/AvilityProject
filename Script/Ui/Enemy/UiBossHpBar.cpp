#include <DxLib.h>
#include "../../Object/Character/Player.h"
#include "../../Manager/Common/ResourceManager.h"
#include "UiBossHpBar.h"

UiBossHpBar::UiBossHpBar(EnemyBase& owner) :
	owner_(owner)
{

}

UiBossHpBar::~UiBossHpBar()
{
}

void UiBossHpBar::Init()
{
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

void UiBossHpBar::Update()
{
}

void UiBossHpBar::Draw()
{
}
