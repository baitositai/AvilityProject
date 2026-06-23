#include <DxLib.h>
#include "../../Manager/Common/ResourceManager.h"
#include "UiPlayerMessages.h"

UiPlayerMessages::UiPlayerMessages(const Player& owner) :
	UiPlayerBase(owner)
{
	handles_ = nullptr;
}

UiPlayerMessages::~UiPlayerMessages()
{
}

void UiPlayerMessages::Init()
{
	// 初期化処理
	UiPlayerBase::Init();

	// 相対位置
	Vector2 localPos = { -81, -25 };

	// 描画位置の設定
	pos_ = Vector2::AddVector2(basePos_, localPos);

	// リソース取得
	handles_ = resourceManager_.GetHandles("playerStatusMessageUis");
}

void UiPlayerMessages::Draw()
{
	for (int i = 0; i < 2; i++)
	{
		DrawRotaGraph(
			pos_.x,
			pos_.y + i * 20,
			1.0f,
			0.0f,
			handles_[i],
			true
		);
	}
}
