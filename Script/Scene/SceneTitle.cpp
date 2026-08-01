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
	titleEaseCnt_ = 0.0f;
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

		float menuPosY = MENU_POS_Y_START + i * MENU_POS_Y_OFFSET;
		float menuStartEasePosX = Application::SCREEN_SIZE_X + menus_[i].GetScaledImageSize().x;
		menuEasingParams_[i].startPos = Vector2(menuStartEasePosX, menuPosY);
		menuEasingParams_[i].goalPos = Vector2(MENU_POS_X, menuPosY);
		menus_[i].pos = menuEasingParams_[i].startPos;
	}
	selectMenuIndex_ = 0;
	menuSpawnDisCount_ = 0.0f;
	// メニューUIの設定
	uiMenu_.handleId = resMng_.GetHandle("menu");
	Vector2 uiMenuSize = uiMenu_.GetScaledImageSize();
	Vector2 initUiMenuPos = Vector2(-uiMenuSize.x,
		-uiMenuSize.y);
	uiMenu_.pos = initUiMenuPos;
	uiMenuEaseParam_.startPos = initUiMenuPos;
	uiMenuEaseParam_.goalPos= Vector2(UI_MENU_POS_X, UI_MENU_POS_Y);

	// メニュー説明の設定
	uiExplanations_.handleIds = resMng_.GetHandles("titleMenuExplanations");
	Vector2 initUiExplanationsPos = Vector2(-uiExplanations_.GetScaledImageSize().x,
		-uiExplanations_.GetScaledImageSize().y);
	uiExplanations_.pos = initUiExplanationsPos;
	uiExplanationsEaseParam_.startPos = initUiExplanationsPos;
	uiExplanationsEaseParam_.goalPos= Vector2(UI_MENU_POS_X, UI_EXPLANATIONS_POS_Y);
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

void SceneTitle::EaseMenuButton(const int menuNum)
{
	//間隔カウントが一定時間たっているかつイージングが終了していなければ,
	//イージングを開始
	if (menuSpawnDisCount_ > MENU_SPAWN_DISTIME && !menuEasingParams_[menuNum].isEndEase && !menuEasingParams_[menuNum].isEasing)
	{
		menuEasingParams_[menuNum].isEasing = true;

		//間隔カウントをリセット
		menuSpawnDisCount_ = 0.0f;
	}
	if (menuEasingParams_[menuNum].isEasing)
	{
		menus_[menuNum].pos.x = UtilityCommon::EaseOutBack(
			menuEasingParams_[menuNum].easeCnt
			, MENU_EASE_TIME
			, menuEasingParams_[menuNum].startPos.x
			, menuEasingParams_[menuNum].goalPos.x);
	}
}

void SceneTitle::EaseMenuAndExplanations(void)
{
	//メニューと説明のイージング
	uiExplanations_.pos.x = UtilityCommon::EaseBounce(uiExplanationsEaseParam_.easeCnt
		, MENU_EXPLANATIONS_NAME_EASE_TIME
		, uiExplanationsEaseParam_.startPos.x
		, uiExplanationsEaseParam_.goalPos.x);
	uiExplanations_.pos.y = UtilityCommon::EaseBounce(uiExplanationsEaseParam_.easeCnt
		, MENU_EXPLANATIONS_NAME_EASE_TIME
		, uiExplanationsEaseParam_.startPos.y
		, uiExplanationsEaseParam_.goalPos.y);
	uiMenu_.pos.x = UtilityCommon::EaseBounce(uiMenuEaseParam_.easeCnt
		, MENU_NAME_EASE_TIME
		, uiMenuEaseParam_.startPos.x
		, uiMenuEaseParam_.goalPos.x);
	uiMenu_.pos.y = UtilityCommon::EaseBounce(uiMenuEaseParam_.easeCnt
		, MENU_NAME_EASE_TIME
		, uiMenuEaseParam_.startPos.y
		, uiMenuEaseParam_.goalPos.y);

	//arrow_.pos = menus_[selectMenuIndex_].pos;
	//arrow_.pos.x -= menus_[selectMenuIndex_].GetScaledImageSize().x / 2;
	//arrow_.pos.y = arrowEaseParam_.startPos.y + ARROW_EASE_LOCAL_Y;
}

void SceneTitle::UpdateMain()
{
	// シーン遷移
	if (inputMng_.IsTrgDown(InputManager::TYPE::SCENE_CHANGE))
	{
		sndMng_.PlaySe(SoundType::SE::DECISION);
		updateTitleFunc_ = std::bind(&SceneTitle::UpdateEaseTitle, this);
		titleLogoStartPosX_ = titleLogo_.pos.x;

		//メニューのイージングの初期化
		for (auto& menuEaseParam : menuEasingParams_)
		{
			menuEaseParam.isEasing = false;
			menuEaseParam.isEndEase = false;
		}
		menuSpawnDisCount_ = 0.0f;
		return;
	}
}

void SceneTitle::UpdateEaseTitle()
{
	if (titleEaseCnt_ >= TITLE_EASE_TIME)
	{
		updateTitleFunc_ = std::bind(&SceneTitle::UpdateSelectEase, this);
		drawTitleFunc_ = std::bind(&SceneTitle::DrawSelect, this);
		titleEaseCnt_ = TITLE_EASE_TIME;

		//選択中メニューのゴール座標がMENU_POS_Xになるようにする
		menuEasingParams_[selectMenuIndex_].goalPos.x = MENU_POS_X;

		return;
	}
	float imgSize= titleLogo_.GetScaledImageSize().x;
	float goalPosX = Application::SCREEN_SIZE_X + titleLogo_.GetScaledImageSize().x;
	titleEaseCnt_ += scnMng_.GetDeltaTime();
	titleLogo_.pos.x = UtilityCommon::EaseInBack(titleEaseCnt_, TITLE_EASE_TIME, titleLogoStartPosX_, goalPosX);
}

void SceneTitle::UpdateEaseTitleBack()
{
	if (titleEaseCnt_ <= 0.0f)
	{
		updateTitleFunc_ = std::bind(&SceneTitle::UpdateMain, this);
		titleEaseCnt_ = 0;
		return;
	}
	float imgSize = titleLogo_.GetScaledImageSize().x;
	float goalPosX = Application::SCREEN_SIZE_X + titleLogo_.GetScaledImageSize().x;
	titleEaseCnt_ -= scnMng_.GetDeltaTime();
	titleLogo_.pos.x = UtilityCommon::EaseInBack(titleEaseCnt_, TITLE_EASE_TIME, titleLogoStartPosX_, goalPosX);
}

void SceneTitle::UpdateSelect()
{
	if (inputMng_.IsTrgDown(InputManager::TYPE::SELECT_DOWN))
	{
		menuEasingParams_[selectMenuIndex_].isEndEase = false;
		selectMenuIndex_ = UtilityCommon::WrapStepIndex(selectMenuIndex_, 1, 0, MENU_COUNT_MAX);
		menuEasingParams_[selectMenuIndex_].isEndEase = false;
		sndMng_.PlaySe(SoundType::SE::SELECT);
		return;
	}
	else if (inputMng_.IsTrgDown(InputManager::TYPE::SELECT_UP))
	{
		menuEasingParams_[selectMenuIndex_].isEndEase = false;
		selectMenuIndex_ = UtilityCommon::WrapStepIndex(selectMenuIndex_, -1, 0, MENU_COUNT_MAX);
		menuEasingParams_[selectMenuIndex_].isEndEase = false;
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

	for (int i = 0; i < MENU_COUNT_MAX; i++)
	{
		//イージングが終了していたら処理を飛ばす
		if (menuEasingParams_[i].isEndEase)continue;

		if (i==selectMenuIndex_)
		{
			//時間が一定時間を超えたらイージング終了
			if (menuEasingParams_[i].easeCnt > MENU_SELECT_EASE_TIME)
			{
				menuEasingParams_[i].isEndEase = true;
				menuEasingParams_[i].isEasing = false;
				menuEasingParams_[i].easeCnt=MENU_SELECT_EASE_TIME;
				continue;
			}
			menuEasingParams_[i].easeCnt += scnMng_.GetDeltaTime();
		}
		else
		{
			if (menuEasingParams_[i].easeCnt < 0.0f)
			{
				menuEasingParams_[i].isEndEase = true;
				menuEasingParams_[i].isEasing = false;
				menuEasingParams_[i].easeCnt = 0.0f;
				continue;
			}
			menuEasingParams_[i].easeCnt -= scnMng_.GetDeltaTime();
		}

		menus_[i].pos.x = UtilityCommon::EaseLerping(
			menuEasingParams_[i].easeCnt
			, MENU_SELECT_EASE_TIME
			, menuEasingParams_[i].startPos.x
			, menuEasingParams_[i].goalPos.x);
	}
}

void SceneTitle::UpdateSelectEase()
{
	auto menuIt = std::find_if(menuEasingParams_.begin(), menuEasingParams_.end()
		, [](EasingParameter& easeParam) {
			return easeParam.isEndEase == false;
		});

	//メニューのイージングがすべて終わっていれば更新を切り替える
	if (menuIt == menuEasingParams_.end())
	{
		updateTitleFunc_ = std::bind(&SceneTitle::UpdateSelect, this);

		//選択中のメニューは横に移動するイージングを開始する
		menuEasingParams_[selectMenuIndex_].isEasing = true;
		menuEasingParams_[selectMenuIndex_].isEndEase = false;
		uiExplanationsEaseParam_.easeCnt = MENU_EXPLANATIONS_NAME_EASE_TIME;
		return;
	}

	//各メニューのイージング
	for (int i = 0; i < MENU_COUNT_MAX; i++)
	{
		//イージングが終了していたら
		if (menuEasingParams_[i].easeCnt > MENU_EASE_TIME
			&& uiExplanationsEaseParam_.easeCnt > MENU_EXPLANATIONS_NAME_EASE_TIME
			&& uiMenuEaseParam_.easeCnt > MENU_NAME_EASE_TIME)
		{
			menuEasingParams_[i].isEndEase = true;
			menuEasingParams_[i].isEasing = false;

			//選択中のメニューは横に移動するイージングを開始する
			menuEasingParams_[i].easeCnt = 0.0f;
			menuEasingParams_[i].startPos = menus_[i].pos;
			menuEasingParams_[i].goalPos = Vector2(MENU_SELECT_POS_X, menus_[i].pos.y);
			continue;
		}

		//メニューを動かす
		EaseMenuButton(i);
		if (menuEasingParams_[i].isEasing)
		{
			menuEasingParams_[i].easeCnt += scnMng_.GetDeltaTime();
		}
	}
	menuSpawnDisCount_ += scnMng_.GetDeltaTime();

	EaseMenuAndExplanations();

	uiExplanationsEaseParam_.easeCnt += scnMng_.GetDeltaTime();
	uiMenuEaseParam_.easeCnt += scnMng_.GetDeltaTime();

}

void SceneTitle::UpdateSelectEaseBack()
{
	auto menuIt = std::find_if(menuEasingParams_.begin(), menuEasingParams_.end()
		, [](EasingParameter& easeParam) {
			return easeParam.isEndEase == false;
		});

	//メニューのイージングがすべて終わっていれば更新を切り替える
	if (menuIt == menuEasingParams_.end()
		&& uiExplanationsEaseParam_.easeCnt<=0.0f
		&& uiMenuEaseParam_.easeCnt<=0.0f)
	{
		updateTitleFunc_ = std::bind(&SceneTitle::UpdateEaseTitleBack, this);
		drawTitleFunc_ = std::bind(&SceneTitle::DrawMain, this);
		return;
	}

	//各メニューのイージング
	for (int i = 0; i < MENU_COUNT_MAX; i++)
	{
		//イージングが終了していたら
		if (menuEasingParams_[i].easeCnt < 0.0f)
		{
			menuEasingParams_[i].isEndEase = true;
			menuEasingParams_[i].isEasing = false;
			menuEasingParams_[i].easeCnt = 0.0f;
			continue;
		}

		//メニューを動かす
		EaseMenuButton(i);
		if (menuEasingParams_[i].isEasing)
		{
			menuEasingParams_[i].easeCnt -= scnMng_.GetDeltaTime();
		}
	}
	menuSpawnDisCount_ += scnMng_.GetDeltaTime();

	EaseMenuAndExplanations();

	uiExplanationsEaseParam_.easeCnt -= scnMng_.GetDeltaTime();
	uiMenuEaseParam_.easeCnt -= scnMng_.GetDeltaTime();
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
		//menu.pos.x = MENU_POS_X;
		menu.scale = 1.0f;
		if (index == selectMenuIndex_)
		{
			//menu.pos.x = MENU_SELECT_POS_X;
			menu.scale = 1.05f;
		}
		menu.DrawRota();
		index++;
	}

	uiExplanations_.index = selectMenuIndex_;
	uiExplanations_.DrawRota();
	uiMenu_.DrawRota();

	//arrow_.DrawRota();
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
	updateTitleFunc_ = std::bind(&SceneTitle::UpdateSelectEaseBack, this);
	for (int i = 0; i < MENU_COUNT_MAX; i++)
	{
		float menuPosY = MENU_POS_Y_START + i * MENU_POS_Y_OFFSET;
		float menuStartEasePosX = Application::SCREEN_SIZE_X + menus_[i].GetScaledImageSize().x;

		menuEasingParams_[i].isEasing = false;
		menuEasingParams_[i].isEndEase = false;
		menuEasingParams_[i].easeCnt = MENU_EASE_TIME;
		menuEasingParams_[i].startPos = Vector2(menuStartEasePosX, menuPosY);
		menuEasingParams_[i].goalPos = menus_[i].pos;
	}
	menuSpawnDisCount_ = 0.0f;

}
