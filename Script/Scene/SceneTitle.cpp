#include <string>
#include <cmath>
#include <DxLib.h>
#include "../Application.h"
#include "../Manager/Common/SceneManager.h"
#include "../Manager/Common/InputManager.h"
#include "../Manager/Common/ResourceManager.h"
#include "../Manager/Common/SoundManager.h"
#include "../Manager/Common/FontManager.h"
#include "../Utility/UtilityCommon.h"
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
	titleLogo_.size = { Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y };

	sndMng_.PlayBgm(SoundType::BGM::TITLE);

	// パラメータ設定
	auto parameterTrain = std::make_unique<ParameterActor>();
	parameterTrain->pos_ = { (float)Application::SCREEN_HALF_X, 800.0f };
	parameterTrain->scale_ = 5.0f;
	parameterTrain->hitSize_ = { 4096, 64 };
	parameterTrain->resourceKey_ = "train";
	parameterTrain->divisionNum_ = { 16, 1 };

	auto parameterCarriage = std::make_unique<ParameterActor>(*parameterTrain);
	parameterCarriage->pos_.x += (float)parameterTrain->hitSize_.x * parameterTrain->scale_;
	parameterCarriage->resourceKey_ = "carriage";

	// オブジェクト定義
	//train_ = std::make_unique<Train>(std::move(parameterTrain));
	//train_->Init();

	//carriage_ = std::make_unique<Train>(std::move(parameterCarriage));
	//carriage_->Init();
}

void SceneTitle::NormalUpdate()
{
	// シーン遷移
	if (inputMng_.IsTrgDown(InputManager::TYPE::DEBUG_SCENE_CHANGE))
	{
		scnMng_.ChangeScene(SceneManager::SCENE_ID::GAME);
		sndMng_.PlaySe(SoundType::SE::GAME_START);
		sndMng_.StopBgm(SoundType::BGM::TITLE);
		return;
	}
}

void SceneTitle::NormalDraw()
{
	titleLogo_.DrawExtend();
	DrawString(0, 0, L"RSHIFTでシーン遷移", UtilityCommon::WHITE);
}