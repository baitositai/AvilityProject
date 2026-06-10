#include <string>
#include <cmath>
#include <DxLib.h>
#include "../Application.h"
#include "../Manager/Common/SceneManager.h"
#include "../Manager/Common/Camera.h"
#include "../Manager/Common/InputManager.h"
#include "../Manager/Common/ResourceManager.h"
#include "../Manager/Common/SoundManager.h"
#include "../Manager/Common/FontManager.h"
#include "../Utility/UtilityCommon.h"
#include "../Object/Stage/BackGround.h"
#include "../Object/Common/Animation.h"
#include "../Object/Stage/Train.h"
#include "SceneTitle.h"

SceneTitle::SceneTitle()
{
	// 更新関数のセット
	updataFunc_ = std::bind(&SceneTitle::LoadingUpdate, this);

	// 描画関数のセット
	drawFunc_ = std::bind(&SceneTitle::LoadingDraw, this);
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Init()
{
	titleLogo_.handleId = resMng_.GetHandle("titleLogo");
	titleLogo_.pos = { Application::SCREEN_HALF_X, Application::SCREEN_HALF_Y - 150 };



	sndMng_.PlayBgm(SoundType::BGM::TITLE);

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
	
	ground_ = std::make_unique<BackGround>();
	ground_->SetResource("titleGround");
	ground_->SetType(BackGround::TYPE::SCROLL);
	ground_->SetScrollSpeed(scrollSpeed);
	mainCamera.ChangeMode(Camera::MODE::TRAIN_SHAKE);
}

void SceneTitle::NormalUpdate()
{
	train_->Update();
	ground_->Update();
	for (auto& backGround : backGround_)
	{
		backGround->Update();
	}

	// シーン遷移
	if (inputMng_.IsTrgDown(InputManager::TYPE::SCENE_CHANGE))
	{
		scnMng_.ChangeScene(SceneManager::SCENE_ID::GAME);
		sndMng_.PlaySe(SoundType::SE::GAME_START);
		sndMng_.StopBgm(SoundType::BGM::TITLE);
		return;
	}
}

void SceneTitle::NormalDraw()
{
	for (auto& backGround : backGround_)
	{
		backGround->Draw();
	}
	ground_->Draw();
	train_->Draw();
	titleLogo_.DrawRota();
	DrawString(0, 0, L"RSHIFTでシーン遷移", UtilityCommon::WHITE);
}