#include "../Application.h"
#include "../Manager/Common/SceneManager.h"
#include "../Manager/Common/SoundManager.h"
#include "../Manager/Common/ResourceManager.h"
#include "../Manager/Game/PlayerManager.h"
#include "../Manager/Game/EnemyManager.h"
#include "GameStart.h"

GameStart::GameStart(const int index) :
	index_(index),
	sceneManager_(SceneManager::GetInstance()),
	soundManager_(SoundManager::GetInstance()),
	playerManager_(PlayerManager::GetInstance()),
	enemyManager_(EnemyManager::GetInstance())
{
	// ‰Šúˆ—‚Ì“o˜^
	update_ = std::bind(&GameStart::UpdateReady, this);

	isEnd_ = false;
	step_ = 0.0f;
	barLength_ = 0.0f;
}

GameStart::~GameStart()
{
}

void GameStart::Init()
{
	auto& resourceManager = ResourceManager::GetInstance();
	mainTitle_.handleId = resourceManager.GetHandle("ready");
	mainTitle_.pos = { Application::SCREEN_HALF_X, Application::SCREEN_HALF_Y };

	subTitle_.handleIds = resourceManager.GetHandles("startMessages");
	subTitle_.pos = { Application::SCREEN_HALF_X, Application::SCREEN_HALF_Y - 140 };
	subTitle_.index = index_;
	
	bar_.handleId = resourceManager.GetHandle("readyBar");
	bar_.size = { 687, 16 };
	bar_.pos = { Application::SCREEN_HALF_X - bar_.size.x / 2, Application::SCREEN_HALF_Y + 100 - bar_.size.y / 2 };
	bar_.size.x = 0;

	// ‰Šúˆ—‚Ì“o˜^
	update_ = std::bind(&GameStart::UpdateReady, this);

	soundManager_.PlaySe(SoundType::SE::READY);
}

void GameStart::Update()
{
	update_();
}

void GameStart::Draw()
{
	mainTitle_.DrawRota();
	subTitle_.DrawRota();
	bar_.DrawExtend();
}

void GameStart::UpdateReady()
{
	constexpr int BAR_LENGTH_MAX = 687;
	constexpr float READY_TIME = 2.0f;

	float deltaTime = sceneManager_.GetDeltaTime();

	if (deltaTime > 0.0f)
	{
		float progressSpeed = static_cast<float>(BAR_LENGTH_MAX) / READY_TIME;
		barLength_ += progressSpeed * deltaTime;
		bar_.size.x = static_cast<int>(barLength_);
	}

	if (bar_.size.x >= BAR_LENGTH_MAX)
	{
		bar_.size.x = BAR_LENGTH_MAX;
		barLength_ = 0.0f;
		bar_.size = { 0, 0 };
		update_ = std::bind(&GameStart::UpdateGo, this);
		mainTitle_.handleId = ResourceManager::GetInstance().GetHandle("go");
		soundManager_.PlaySe(SoundType::SE::GO);
		soundManager_.PlaySe(SoundType::SE::GONG);
	}
}

void GameStart::UpdateGo()
{
	constexpr float GO_TIME = 1.0f;
	step_ += sceneManager_.GetDeltaTime();

	float rate = step_ / GO_TIME;
	if (rate > 1.0f)
	{
		rate = 1.0f;
	}

	if (rate < 0.2f)
	{
		float subRate = rate / 0.2f;
		mainTitle_.scale = 0.0f + (1.3f - 0.0f) * subRate;
	}
	else if (rate < 0.4f)
	{
		float subRate = (rate - 0.2f) / 0.2f;
		mainTitle_.scale = 1.3f + (1.0f - 1.3f) * subRate;
	}
	else if (rate < 0.8f)
	{
		mainTitle_.scale = 1.0f;
	}
	else
	{
		float subRate = (rate - 0.8f) / 0.2f;
		mainTitle_.scale = 1.0f + (0.0f - 1.0f) * subRate;
		subTitle_.scale = 1.0f + (0.0f - 1.0f) * subRate;
	}

	if (step_ >= GO_TIME)
	{
		isEnd_ = true;
	}
}