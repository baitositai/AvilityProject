#include <DxLib.h>
#include "../Application.h"
#include "../Manager/Common/ResourceManager.h"
#include "../Manager/Common/SoundManager.h"
#include "../Manager/Common/SoundType.h"
#include "../Manager/Common/FontManager.h"
#include "../Manager/Common/SceneManager.h"
#include "../Manager/Common/Camera.h"
#include "../Utility/UtilityCommon.h"
#include "ScenePause.h"

ScenePause::ScenePause()
{
	PadNo_ = Input::JOYPAD_NO::PAD1;

	//更新関数のセット
	updataFunc_ = std::bind(&ScenePause::NormalUpdate, this);
	//描画関数のセット
	drawFunc_ = std::bind(&ScenePause::NormalDraw, this);

	pauseFont_ = -1;
	selectIndex_ = 0;
	
	//リストごとに処理を分ける
	listFuncTable_ =
	{
		{LIST::RESUME,[this]()
		{
			// ポーズを解除して前のシーンに戻る
			scnMng_.PopScene();
			mainCamera.PauseRestart();
		}},
		{LIST::NONE,[this]()
		{
			
		}},
		{LIST::TITLE,[this]()
		{
			// タイトルシーンに戻る
			scnMng_.ChangeScene(SceneManager::SCENE_ID::TITLE);
		}},
		{LIST::GAME_END,[this]()
		{
			// ゲーム終了
			Application::GetInstance().GameEnd();
		}}
	};

	pauseFont_ = fontMng_.CreateMyFont(resMng_.GetFontName("fontKazuki"), FONT_SIZE, FONT_THICK);

	// リソースの取得と同時に必要な情報を取得
	handleIds_ = resMng_.GetHandles("pauseSprite");
	
	//const auto texture = resMng_.GetResourceTexture(GetParameter().resourceKey_);
	//GetParameter().drawSize_ = texture->GetSize();
	//GetParameter().divisionNum_ = texture->GetDivsion();
	//GetParameter().drawHalfSize_ = Vector2(GetParameter().drawSize_.x / 2, GetParameter().drawSize_.y / 2);
	

	//pauseSprite
}

ScenePause::ScenePause(Input::JOYPAD_NO PadNo)
	:
	PadNo_(PadNo)
{
	//更新関数のセット
	updataFunc_ = std::bind(&ScenePause::NormalUpdate, this);
	//描画関数のセット
	drawFunc_ = std::bind(&ScenePause::NormalDraw, this);

	pauseFont_ = -1;
	selectIndex_ = 0;

	//リストごとに処理を分ける
	listFuncTable_ =
	{
		{LIST::RESUME,[this]()
		{
			// ポーズを解除して前のシーンに戻る
			scnMng_.ResetPausePadNo();
			scnMng_.PopScene();
			mainCamera.PauseRestart();
		}},
		{LIST::NONE,[this]()
		{

		}},
		{LIST::TITLE,[this]()
		{
			// タイトルシーンに戻る
			scnMng_.ResetPausePadNo();
			scnMng_.ChangeScene(SceneManager::SCENE_ID::TITLE);
		}},
		{LIST::GAME_END,[this]()
		{
			// ゲーム終了
			Application::GetInstance().GameEnd();
		}}
	};

	pauseFont_ = fontMng_.CreateMyFont(resMng_.GetFontName("fontKazuki"), FONT_SIZE, FONT_THICK);

	// リソースの取得と同時に必要な情報を取得
	handleIds_ = resMng_.GetHandles("pauseSprite");
}

ScenePause::~ScenePause()
{
	
}

void ScenePause::NormalUpdate()
{
	// Pauseボタンでの更新はSceneManagerにて行っている
	if (inputMng_.IsTrgDown(InputManager::TYPE::SELECT_DOWN, PadNo_))
	{
		selectIndex_ = UtilityCommon::WrapStepIndex(selectIndex_, 1, 0, LIST_MAX);
		return;
	}
	else if (inputMng_.IsTrgDown(InputManager::TYPE::SELECT_UP, PadNo_))
	{
		selectIndex_ = UtilityCommon::WrapStepIndex(selectIndex_, -1, 0, LIST_MAX);
		return;
	}
	else if (inputMng_.IsTrgDown(InputManager::TYPE::SELECT_DECISION, PadNo_))
	{
		SoundManager::GetInstance().PlaySe(SoundType::SE::DECISION);
		listFuncTable_[static_cast<LIST>(selectIndex_)]();
		return;
	}
}

void ScenePause::NormalDraw()
{
	static constexpr int MARGINT = 0;
	static constexpr int OFFSET_Y = 160;
	static constexpr int TEXT_MARGINT = 100;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, PAUSE_ALPHA);
	DrawBox(
		MARGINT,
		MARGINT,
		Application::SCREEN_SIZE_X- MARGINT,
		Application::SCREEN_SIZE_Y- MARGINT,
		UtilityCommon::BLACK,
		true);	
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	for (int i = 0; i < LIST_MAX; ++i)
	{
		//座標位置を設定
		int posX = Application::SCREEN_HALF_X;
		int posY = Application::SCREEN_HALF_Y - OFFSET_Y + TEXT_MARGINT * i;

		if (i == selectIndex_)
		{
			// 選択中の場合は赤色強調（赤成分:255, 緑成分:100, 青成分:100）
			// ※画像の色合いに合わせて RGB の値を調整してください
			SetDrawAddColor( 0, -255, -255);
		}

		DrawRotaGraph(posX, posY, 1.0f, 0.0f, handleIds_[i], true);

		// 描画モードや輝度を元に戻しておく
		SetDrawAddColor(0, 0, 0);
	}
}