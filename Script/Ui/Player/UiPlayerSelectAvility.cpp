#include "../../Manager/Common/ResourceManager.h"
#include "../../Object/Character/Player.h"
#include "UiPlayerSelectAvility.h"

UiPlayerSelectAvility::UiPlayerSelectAvility(const Player& owner) :
	UiPlayerBase(owner)
{
}

UiPlayerSelectAvility::~UiPlayerSelectAvility()
{
}

void UiPlayerSelectAvility::Init()
{
	UiPlayerBase::Init();

	// リソース取得
	handle_ = resourceManager_.GetHandle("playerSelectAvility");
	barHandle_ = resourceManager_.GetHandle("playerSelectAvilityBar");
	
	// バー設定
	barSize_ = { 263, 28 };
	barLength_ = (float)barSize_.x;

	// 位置
	Vector2 localPos_ = { -86, -50 };
	pos_ = Vector2::AddVector2(basePos_, localPos_);
	barPos_ = { pos_.x - barSize_.x / 2, pos_.y - barSize_.y / 2 };
}

void UiPlayerSelectAvility::Update()
{
	// 所有者が死んでいた場合終了
	if (CheckOwnerDead()) { return; }

	float time = owner_.GetParameter().selectAvilityTime_;
	if (time > 0.0f)
	{
		isActive_ = true;
		float value = static_cast<float>(barSize_.x) / Player::AVILITY_SELECT_TIME;
		barLength_ = value * time;
	}
	else
	{
		barLength_ = 0.0f;
		isActive_ = false;
	}
}

void UiPlayerSelectAvility::Draw()
{
	if (isActive_)
	{
		// 残り時間のバーを表示
		DrawExtendGraph(
			barPos_.x,
			barPos_.y,
			barPos_.x + (int)barLength_,
			barPos_.y + barSize_.y,
			barHandle_,
			true
		);

		// メッセージの描画
		DrawRotaGraph(
			pos_.x,
			pos_.y,
			scale_,
			angle_,
			handle_,
			true
		);
	}
}
