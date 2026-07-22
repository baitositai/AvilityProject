#include <DxLib.h>
#include "../../Application.h"
#include "../../Manager/Common/ResourceManager.h"
#include "../../System/PlayerCheckAnnihilation.h"
#include "../Common/UiTimer.h"
#include "UiPlayerAnnhilation.h"

UiPlayerAnnhilation::UiPlayerAnnhilation(const PlayerCheckAnnihilation& owner) :
	owner_(owner)
{
}

UiPlayerAnnhilation::~UiPlayerAnnhilation()
{
}

void UiPlayerAnnhilation::Init()
{
	// 描画位置の設定
	pos_ = { Application::SCREEN_HALF_X, 200 };

	// リソース取得
	handle_ = resourceManager_.GetHandle("uiPlayerAnnhilationMessage");

	// 大きさの指定
	scale_ = 1.0f;

	// タイマー
	uiTimer_ = std::make_unique<UiTimer>();
	uiTimer_->Init();
	uiTimer_->SetParameter(Vector2(Application::SCREEN_HALF_X, Application::SCREEN_HALF_Y + 50), owner_.GetTimer(), 2.0f);

	// 活動判定
	isActive_ = false;
}

void UiPlayerAnnhilation::Draw()
{
	if (isActive_)
	{
		// 赤色にする
		SetDrawAddColor(0, -255, -255);

		// UIの描画
		DrawRotaGraph(
			pos_.x,
			pos_.y,
			scale_,
			angle_,
			handle_,
			true
		);

		// タイマーの描画
		uiTimer_->SetNumber(owner_.GetTimer());
		uiTimer_->Draw();

		// 加算分を戻す
		SetDrawAddColor(0, 0, 0);
	}
}