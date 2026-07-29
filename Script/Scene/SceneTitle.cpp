#include <string>
#include <cmath>
#include <DxLib.h>
#include "../Application.h"
#include "../Manager/Common/SceneManager.h"
#include "../Manager/Common/Camera.h"
#include "../Manager/Common/InputManager.h"
#include "../Manager/Common/ResourceManager.h"
#include "../Manager/Common/SoundManager.h"
#include "../Manager/Common/ScoreManager.h"
#include "../Manager/Common/FontManager.h"
#include "../Manager/Game/PlayerManager.h"
#include "../Utility/UtilityCommon.h"
#include "../Object/Stage/BackGround.h"
#include "../Object/Common/Animation.h"
#include "../Object/Stage/Train.h"
#include "SceneTitle.h"

SceneTitle::SceneTitle()
{
	// 処理の登録
	updataFunc_ = std::bind(&SceneTitle::LoadingUpdate, this);
	drawFunc_ = std::bind(&SceneTitle::LoadingDraw, this);
	updateTitleFunc_ = std::bind(&SceneTitle::UpdateMain, this);
	drawTitleFunc_ = std::bind(&SceneTitle::DrawMain, this);
	changeMap_.emplace(MENU::TUTORIAL, std::bind(&SceneTitle::ChangeMenuTutorial, this));
	changeMap_.emplace(MENU::START, std::bind(&SceneTitle::ChangeMenuGame, this));
	changeMap_.emplace(MENU::ABILITY_TRIAL, std::bind(&SceneTitle::ChangeMenuAbilityTrial, this));
	changeMap_.emplace(MENU::BACK, std::bind(&SceneTitle::ChangeMenuBack, this));

	// 変数の初期化
	selectMenuIndex_ = -1;
	alphaRate_ = 0.0f;
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Init()
{
	// カメラ位置リセット
	mainCamera.SetCameraPos(Vector2F());

	// UI
	titleLogo_.handleId = resMng_.GetHandle("titleLogo");
	titleLogo_.pos = { Application::SCREEN_HALF_X, Application::SCREEN_HALF_Y - 150 };

	pleaseButton_.handleId = resMng_.GetHandle("pleaseButton");
	pleaseButton_.pos = { Application::SCREEN_HALF_X, Application::SCREEN_HALF_Y + 170 };

	// パラメータ設定
	auto parameterTrain = std::make_unique<ParameterActor>();
	parameterTrain->scale_ = 4.5f;
	parameterTrain->hitSize_ = { 4096, 64 };
	parameterTrain->resourceKey_ = "train";
	parameterTrain->divisionNum_ = { 16, 1 };
	parameterTrain->componentkeys_ = { "spriteAnimation" };
	parameterTrain->animationDataMap_ = { {"walk", Animation::Data{ 0,15, 0.3f}} };
	parameterTrain->pos_ = { (float)Application::SCREEN_HALF_X, 
		(float)Application::SCREEN_SIZE_Y - (float)parameterTrain->hitSize_.y * parameterTrain->scale_ / 2.0f - 62.0f };

	// オブジェクト定義
	train_ = std::make_unique<Train>(std::move(parameterTrain));
	train_->Init();
	train_->GetAnimation().Play(Animation::TYPE::WALK);

	// 背景設定
	int index = 0;
	float scrollSpeed = -0.5f;
	float addScrollSpeed = -0.2f;
	for (auto& backGround : backGround_)
	{
		backGround = std::make_unique<BackGround>();
		backGround->SetType(BackGround::TYPE::SCROLL);
		backGround->SetScrollSpeed(scrollSpeed);
		backGround->SetResource("backGround" + std::to_string(index));
		index++;
		scrollSpeed += addScrollSpeed;
	}	
	
	// 地面
	ground_ = std::make_unique<BackGround>();
	ground_->SetResource("titleGround");
	ground_->SetType(BackGround::TYPE::SCROLL);
	ground_->SetScrollSpeed(scrollSpeed);

	// カメラ
	mainCamera.ChangeMode(Camera::MODE::TRAIN_SHAKE);

	// BGM再生
	sndMng_.PlayBgm(SoundType::BGM::TRAIN);

	// SE再生
	sndMng_.PlaySe(SoundType::SE::TRAIN_WHISTLE);

	// メニュー項目設定
	int* handles = resMng_.GetHandles("uiTitle");
	for (int i = 0; i < MENU_COUNT_MAX; i++)
	{
		menus_[i].handleId = handles[i];
		menus_[i].scale = 1.0f;
		menus_[i].pos = Vector2(MENU_POS_X, MENU_POS_Y_START + i * MENU_POS_Y_OFFSET);
	}
	selectMenuIndex_ = 0;

	// メニューUIの設定
	uiMenu_.handleId = resMng_.GetHandle("menu");
	uiMenu_.pos = Vector2(UI_MENU_POS_X, UI_MENU_POS_Y);

	// メニュー説明の設定
	uiExplantions_.handleIds = resMng_.GetHandles("titleMenuExplanations");
	uiExplantions_.pos = Vector2(UI_MENU_POS_X, UI_EXPLANATIONS_POS_Y);
}

void SceneTitle::NormalUpdate()
{
	train_->Update();
	ground_->Update();
	for (auto& backGround : backGround_)
	{
		backGround->Update();
	}
	updateTitleFunc_();
}

void SceneTitle::NormalDraw()
{
	for (auto& backGround : backGround_)
	{
		backGround->Draw();
	}
	ground_->Draw();
	train_->Draw();
	drawTitleFunc_();
}

void SceneTitle::UpdateMain()
{
	// シーン遷移
	if (inputMng_.IsTrgDown(InputManager::TYPE::SCENE_CHANGE))
	{
		sndMng_.PlaySe(SoundType::SE::DECISION);
		updateTitleFunc_ = std::bind(&SceneTitle::UpdateSelect, this);
		drawTitleFunc_ = std::bind(&SceneTitle::DrawSelect, this);
		return;
	}

}

void SceneTitle::UpdateSelect()
{
	if (inputMng_.IsTrgDown(InputManager::TYPE::SELECT_DOWN))
	{
		selectMenuIndex_ = UtilityCommon::WrapStepIndex(selectMenuIndex_, 1, 0, MENU_COUNT_MAX);
		sndMng_.PlaySe(SoundType::SE::SELECT);
		return;
	}
	else if (inputMng_.IsTrgDown(InputManager::TYPE::SELECT_UP))
	{
		selectMenuIndex_ = UtilityCommon::WrapStepIndex(selectMenuIndex_, -1, 0, MENU_COUNT_MAX);
		sndMng_.PlaySe(SoundType::SE::SELECT);
		return;
	}
	else if (inputMng_.IsTrgDown(InputManager::TYPE::SELECT_DECISION))
	{
		SoundManager::GetInstance().PlaySe(SoundType::SE::DECISION);
		sndMng_.PlaySe(SoundType::SE::DECISION);
		changeMap_[static_cast<MENU>(selectMenuIndex_)]();
		return;
	}
}

void SceneTitle::DrawMain()
{
	titleLogo_.DrawRota();

	// 点滅の1周期にかかる時間
	constexpr int BLINK_CYCLE_MS = 3200;

	// 現在の時間を取得
	int nowTime = GetNowCount();

	// 周期に基づいて角度を計算
	float currentAngle = (nowTime % BLINK_CYCLE_MS) * DX_PI_F * 2.0f / static_cast<float>(BLINK_CYCLE_MS);

	// サイン波を使って範囲変換
	int alphaValue = static_cast<int>((sin(currentAngle) + 1.0f) * (UtilityCommon::ALPHA_MAX / 2.0f));

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alphaValue);
	pleaseButton_.DrawRota();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SceneTitle::DrawSelect()
{
	int index = 0;
	for (auto& menu : menus_)
	{
		menu.pos.x = MENU_POS_X;
		menu.scale = 1.0f;
		if (index == selectMenuIndex_)
		{
			menu.pos.x = MENU_SELECT_POS_X;
			menu.scale = 1.05f;
		}
		menu.DrawRota();
		index++;
	}

	uiExplantions_.index = selectMenuIndex_;
	uiExplantions_.DrawRota();
	uiMenu_.DrawRota();
}

void SceneTitle::ChangeMenuGame()
{
	scnMng_.ChangeScene(SceneManager::SCENE_ID::TRAIN);
	sndMng_.PlaySe(SoundType::SE::DECISION);
	sndMng_.StopBgm(SoundType::BGM::TRAIN);
	scoreManager_.Clear();
	scoreManager_.AddTotalScore(10000);	// 初期スコア
	playerMng_.Create();
}

void SceneTitle::ChangeMenuTutorial()
{
	scnMng_.ChangeScene(SceneManager::SCENE_ID::TRAIN);
	sndMng_.PlaySe(SoundType::SE::DECISION);
	sndMng_.StopBgm(SoundType::BGM::TRAIN);
	scoreManager_.Clear();
	playerMng_.Create();
}

void SceneTitle::ChangeMenuAbilityTrial()
{
	scnMng_.ChangeScene(SceneManager::SCENE_ID::ABILITYROOM);
	sndMng_.PlaySe(SoundType::SE::DECISION);
	sndMng_.StopBgm(SoundType::BGM::TRAIN);
	scoreManager_.Clear();
	playerMng_.Create();
}

void SceneTitle::ChangeMenuBack()
{
	updateTitleFunc_ = std::bind(&SceneTitle::UpdateMain, this);
	drawTitleFunc_ = std::bind(&SceneTitle::DrawMain, this);
}
