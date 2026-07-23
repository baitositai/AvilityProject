#include <DxLib.h>
#include "../Application.h"
#include "../Manager/Common/SceneManager.h"
#include "../Manager/Common/InputManager.h"
#include "../Manager/Common/ResourceManager.h"
#include "../Manager/Common/SoundManager.h"
#include "../Manager/Common/FontManager.h"
#include "../Manager/Common/ScoreManager.h"
#include "../Manager/Game/PlayerManager.h"
#include "../Manager/Game/ItemManager.h"
#include "../Render/PixelMaterial.h"
#include "../Render/PixelRenderer.h"
#include "../Utility/UtilityCommon.h"
#include "../Object/Stage/BackGround.h"
#include "SceneResult.h"

SceneResult::SceneResult()
	:
	score_(0.0f),
	resulTime_(0.0f),
	handleIds_(nullptr)
{
	// 更新関数のセット
	updataFunc_ = std::bind(&SceneResult::LoadingUpdate, this);

	// 描画関数のセット
	drawFunc_ = std::bind(&SceneResult::LoadingDraw, this);

	// 選択中のインデックス
	selectIndex_ = 0;

	//リストごとに処理を分ける
	listFuncTable_ =
	{
		{LIST::RESUME,[this]()
		{
			scnMng_.ChangeScene(SceneManager::SCENE_ID::TRAIN);
			sndMng_.StopBgm(SoundType::BGM::RESULT);
			playerMng_.AllDetachItem();
			playerMng_.Clear();
			itemMng_.SetAllIsCarry(true);
		}},
		{LIST::TITLE,[this]()
		{
			// タイトルシーンに戻る
			scnMng_.ChangeScene(SceneManager::SCENE_ID::TITLE);
			sndMng_.StopBgm(SoundType::BGM::RESULT);
			playerMng_.AllDetachItem();
			playerMng_.Clear();
			itemMng_.SetAllIsCarry(false);
		}},
	};
}

SceneResult::~SceneResult()
{
}

void SceneResult::Init()
{

	scoreManager_.AddScore(playerMng_.GetTotalLootTreasuresMoney());

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

	// 選択UIの読み込み
	listImage_[LIST::TITLE].handleId = resMng_.GetHandle("backTitle");
	listImage_[LIST::RESUME].handleId = resMng_.GetHandle("backGame");

	// 更新スコア
	score_ = 0.0f;
	
	// 待ち時間
	resulTime_ = 0.0f;

	sndMng_.PlayBgm(SoundType::BGM::RESULT);

	// スコアによって読み込む画像を変更する
	auto score = scoreManager_.GetScore();
	if (score >= 100000)
	{
		rank_.handleId = resMng_.GetHandles("ranks")[0];
	}
	else if (score >= 50000)
	{
		rank_.handleId = resMng_.GetHandles("ranks")[1];
	}
	else if (score >= 30000)
	{
		rank_.handleId = resMng_.GetHandles("ranks")[2];
	}
	else if (score >= 10000)
	{
		rank_.handleId = resMng_.GetHandles("ranks")[3];
	}
	else
	{
		rank_.handleId = resMng_.GetHandles("ranks")[4];
	}

	// リソースの取得と同時に必要な情報を取得
	handleIds_ = resMng_.GetHandles("numbers");
	gold_.handleId = resMng_.GetHandle("gold");
	result_.handleId = resMng_.GetHandle("result");
	totalScoreEarned_.handleId = resMng_.GetHandle("totalScoreEarned");
	rank_.scale = 0.0f;
}

void SceneResult::NormalUpdate()
{
	for (auto& backGround : backGround_)
	{
		backGround->Update();
	}

	if (resulTime_ < 0.5f)
	{
		resulTime_ += SceneManager::GetInstance().GetDeltaTime();
		return;
	}

	int targetScore = scoreManager_.GetScore();

	// スコアの描画が終わったらランクを表示する
	if (static_cast<int>(score_) >= targetScore)
	{
		rank_.scale = 1.2f;

		resulTime_ = 0.0f;

		// 更新関数のセット
		updataFunc_ = std::bind(&SceneResult::SecondUpdate, this);

		// 描画関数のセット
		drawFunc_ = std::bind(&SceneResult::SecondDraw, this);

		return;
	}
	else
	{
		// 演出用のスコア変動
		score_ = std::lerp(score_, static_cast<float>(targetScore), 0.05f);

		// 目標値との差が1未満になったら強制的に到達させる
		if (targetScore - score_ < 1.0f)
		{
			score_ = static_cast<float>(targetScore);
		}
	}
}

void SceneResult::SecondUpdate()
{
	for (auto& backGround : backGround_)
	{
		backGround->Update();
	}

	rank_.scale = std::lerp(rank_.scale, 1.0f, 0.1f);

	// 選択の変更
	if (inputMng_.IsTrgDown(InputManager::TYPE::SELECT_RIGHT))
	{
		selectIndex_ = UtilityCommon::WrapStepIndex(selectIndex_, 1, 0, LIST_MAX);
		return;
	}
	else if (inputMng_.IsTrgDown(InputManager::TYPE::SELECT_LEFT))
	{
		selectIndex_ = UtilityCommon::WrapStepIndex(selectIndex_, -1, 0, LIST_MAX);
		return;
	}
	else if (inputMng_.IsTrgDown(InputManager::TYPE::SELECT_DECISION))
	{
		SoundManager::GetInstance().PlaySe(SoundType::SE::DECISION);
		listFuncTable_[static_cast<LIST>(selectIndex_)]();
		return;
	}

}

void SceneResult::NormalDraw()
{
	for (auto& backGround : backGround_)
	{
		backGround->Draw();
	}

	//scoreText_.DrawFormatCenter();
	DrawRotaGraph(Application::SCREEN_HALF_X, 150, 1.0f, 0.0f, result_.handleId, true);
	DrawRotaGraph(Application::SCREEN_HALF_X / 2, 280, 1.0f, 0.0f, totalScoreEarned_.handleId, true);

	// スコアの描画
	ScoreDraw();

	// ランクの描画
	DrawRotaGraph(Application::SCREEN_SIZE_X - 200, Application::SCREEN_HALF_Y, rank_.scale, 0.3f, rank_.handleId, true);

}

void SceneResult::SecondDraw()
{
	NormalDraw();

	static constexpr int MARGINT = 0;
	static constexpr int OFFSET_X = Application::SCREEN_HALF_X / 2;
	static constexpr int OFFSET_Y = Application::SCREEN_HALF_Y / 2;
	static constexpr int TEXT_MARGINT = Application::SCREEN_HALF_X;

	for (int i = 0; i < LIST_MAX; ++i)
	{
		//座標位置を設定
		int posX = Application::SCREEN_HALF_X - OFFSET_X + TEXT_MARGINT * i;
		int posY = Application::SCREEN_HALF_Y + OFFSET_Y;

		if (i == selectIndex_)
		{
			// 選択中の場合は赤色強調（赤成分:255, 緑成分:100, 青成分:100）
			// ※画像の色合いに合わせて RGB の値を調整してください
			SetDrawAddColor(0, -255, -255);
		}

		// 選択肢の描画
		auto listImageIt = listImage_.find(static_cast<LIST>(i));
		if (listImageIt != listImage_.end())
		{
			DrawRotaGraph(posX, posY, 1.0f, 0.0f, listImageIt->second.handleId, true);
		}

		// 描画モードや輝度を元に戻しておく
		SetDrawAddColor(0, 0, 0);
	}
}

void SceneResult::ScoreDraw()
{
	// =========================================================
	// 画像（スプライト）によるスコア描画
	// =========================================================
	if (handleIds_ != nullptr)
	{
		// 1. 描画位置と画像サイズの指定
		int centerX = Application::SCREEN_HALF_X;
		int centerY = 380;

		// 画像のサイズをDxLibから自動取得（または直接数値で指定してもOKです）
		int spriteWidth = 0, spriteHeight = 0;
		GetGraphSize(handleIds_[0], &spriteWidth, &spriteHeight);
		spriteWidth -= 10;

		int spacing = 4; // 数字画像同士の間隔(px)

		// 2. スコアを整数化して文字列に変換
		std::string scoreStr = std::to_string(static_cast<int>(score_));
		int digitCount = static_cast<int>(scoreStr.length());

		// 3. 中央揃えにするための描画開始X座標を計算
		int totalWidth = ((digitCount + 1) * spriteWidth) /*+ ((digitCount - 1) * spacing)*/;
		int startX = centerX - (totalWidth / 2);

		// 4. 1桁ずつ描画
		for (int i = 0; i < digitCount; ++i)
		{
			// 文字から数値（0～9）を取得
			int num = scoreStr[i] - '0';

			// 0～9の範囲内であることを確認して描画
			if (num >= 0 && num <= 9)
			{
				int drawX = startX + i * (spriteWidth /*+ spacing*/);
				int drawY = centerY - (spriteHeight / 2);

				DrawGraph(drawX, drawY, handleIds_[num], TRUE);
			}
		}
		// Gの表示
		DrawGraph(startX + digitCount * (spriteWidth /*+ spacing*/), centerY - (spriteHeight / 2), gold_.handleId, TRUE);
	}
}
