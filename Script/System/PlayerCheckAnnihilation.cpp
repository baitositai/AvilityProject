#include "../Manager/Common/SceneManager.h"
#include "../Manager/Game/PlayerManager.h"
#include "../Manager/Game/UiManager.h"
#include "../Ui/Game/UiPlayerAnnhilation.h"
#include "PlayerCheckAnnihilation.h"

PlayerCheckAnnihilation::PlayerCheckAnnihilation() :
	sceneManager_(SceneManager::GetInstance()),
	playerManager_(PlayerManager::GetInstance())
{
	timer_ = 0.0f;
	isPreAnnihilation_ = false;
	uiPlayerAnnhilation_ = nullptr;
	changeFunctionMap_.emplace(true, std::bind(&PlayerCheckAnnihilation::ChnageAnnihilation, this));
	changeFunctionMap_.emplace(false, std::bind(&PlayerCheckAnnihilation::ChangeAlive, this));
}

PlayerCheckAnnihilation::~PlayerCheckAnnihilation()
{
}

void PlayerCheckAnnihilation::Init()
{
	timer_ = END_TIME;
}

void PlayerCheckAnnihilation::Update()
{
	// プレイヤーの全滅判定を取得
	bool isAnnihilation = playerManager_.IsPlayerAnnihilation();
	if (isAnnihilation != isPreAnnihilation_)
	{
		changeFunctionMap_[isAnnihilation]();
	}

	// タイマーカウント
	if (isAnnihilation)
	{
		timer_ -= sceneManager_.GetDeltaTime();
		if (timer_ < 0.0f)
		{
			sceneManager_.ChangeScene(SceneManager::SCENE_ID::GAMEOVER);

		}
	}

	// バックアップ
	isPreAnnihilation_ = isAnnihilation;
}

void PlayerCheckAnnihilation::ChnageAnnihilation()
{	
	timer_ = END_TIME;
	if (!uiPlayerAnnhilation_)
	{
		auto ui = std::make_unique<UiPlayerAnnhilation>(*this);
		uiPlayerAnnhilation_ = ui.get();
		UiManager::GetInstance().Add(std::move(ui));
	}
	uiPlayerAnnhilation_->SetIsActive(true);
}

void PlayerCheckAnnihilation::ChangeAlive()
{
	if (uiPlayerAnnhilation_)
	{
		uiPlayerAnnhilation_->SetIsActive(false);
	}
}
