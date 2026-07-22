#include "../../Object/Character/Player.h"
#include "../../Manager/Common/ResourceManager.h"
#include "UiPlayerRespawnMessage.h"

UiPlayerRespawnMessage::UiPlayerRespawnMessage(const Player& player) :
	UiPlayerBase(player)
{
	rate_ = 0.0f;
}

UiPlayerRespawnMessage::~UiPlayerRespawnMessage()
{
}

void UiPlayerRespawnMessage::Init()
{
	// 初期化処理
	UiPlayerBase::Init();

	// 相対位置
	Vector2 localPos = { -81, -25 };

	// 描画位置の設定
	pos_ = Vector2::AddVector2(basePos_, localPos);

	// リソース取得
	handle_ = resourceManager_.GetHandle("respawnMessage");

	scale_ = 1.0f;
	rate_ = 1.0f;
}

void UiPlayerRespawnMessage::Update()
{
	scale_ += rate_ * SCALE_RATE;
	if (scale_ > SCALE_MAX || SCALE_MIN > scale_)
	{
		rate_ *= -1.0f;
	}

	if (owner_.GetState() == Player::STATE::ALIVE)
	{
		Delete();
	}
}