#include <DxLib.h>
#include "../Application.h"
#include "../Manager/Common/SceneManager.h"
#include "../Manager/Common/Camera.h"
#include "../Manager/Common/InputManager.h"
#include "../Manager/Common/SoundManager.h"
#include "../Manager/Common/FontManager.h"
#include "../Manager/Common/SpriteEffectManager.h"
#include "../Manager/Common/ScoreManager.h"
#include "../Manager/Common/ResourceManager.h"
#include "../Manager/Game/GameManager.h"
#include "../Manager/Game/PlayerManager.h"
#include "../Manager/Game/CollisionManager.h"
#include "../Manager/Game/GimmickManager.h"
#include "../Manager/Game/EnemyManager.h"
#include "../Manager/Game/StageManager.h"
#include "../Manager/Game/ItemManager.h"
#include "../Manager/Game/UiManager.h"
#include "../Manager/Game/EventManager.h"
#include "../Factory/FactoryComponent.h"
#include "../Utility/UtilityCommon.h"
#include "../System/GameStart.h"
#include "ScenePause.h"
#include "SceneGame.h"

SceneGame::SceneGame()
{
	// 処理の登録
	updataFunc_ = std::bind(&SceneGame::LoadingUpdate, this);
	drawFunc_ = std::bind(&SceneGame::LoadingDraw, this);
	gameUpdate_ = std::bind(&SceneGame::UpdateGameStart, this);

	// 管理クラスの生成
	EventManager::CreateInstance();
	//GameManager::CreateInstance();

	soundType_ = SoundType::BGM::GAME1;
}

SceneGame::~SceneGame()
{
	// 管理クラスの解放
	EventManager::GetInstance().Destroy();
	
	// BGMの停止
	//sndMng_.StopBgm(soundType_);
}

void SceneGame::Init()
{	
	EventManager& eventManager = EventManager::GetInstance();

	// ステージ生成
	stageMng_.Create(StageManager::TYPE::ROAD);

	// 基底クラスの処理
	SceneBase::Init();	

	// 敵の生成処理
	enemyMng_.Generator(stageMng_.GetEnemyAreaPositions());	

	// アイテムの生成処理
	itemMng_.CreateItemList(stageMng_.GetItemCreatePositions());

	// ボス部屋用のドアの生成
	gimmickMng_.CreateBossDoor(stageMng_.GetBossDoorPos());
	
	// イベントの生成
	eventManager.Create(stageMng_.GetEventTriggerPositions());

	// イベント関係の初期化
	eventManager.Init();
	
	// プレイヤーの初期位置を決定
	playerMng_.SetFirstPositions(stageMng_.GetPlayerFirstPositions());

	// カメラ設定
	mainCamera.ChangeMode(Camera::MODE::CAMERA_SCROLL);

	// カメラの移動制限を設定
	Vector2 stageSize = stageMng_.GetStageSize();
	mainCamera.SetCameraLimit(Vector2F{ 0.0f, 0.0f }, stageSize.ToVector2F());

	// 電車追加
	GimmickManager::CreateParameter trainParameter = {};
	trainParameter.type = GimmickTypes::TYPE::TRAIN;
	gimmickMng_.Create(trainParameter);

	// UI作成
	uiMng_.CreateGameUi();

	// サウンド再生
	soundType_ = SoundType::GetRandomGameBgm();
	sndMng_.PlayBgm(soundType_);

	// 操作説明UIの表示
	uiMng_.SetExplanationType(UiExplanations::TYPE::MOVE);
	uiMng_.SetExplanationType(UiExplanations::TYPE::DASH);
	uiMng_.SetExplanationType(UiExplanations::TYPE::JUMP);
	uiMng_.SetExplanationType(UiExplanations::TYPE::THROW);
	uiMng_.SetExplanationType(UiExplanations::TYPE::ATTACK);

	// ゲーム開始処理
	gameStart_ = std::make_unique<GameStart>(0);
	gameStart_->Init();
}

void SceneGame::NormalUpdate()
{
	gameUpdate_();

	// 基底クラスの処理
	SceneBase::NormalUpdate();

	// イベント関係の更新
	EventManager::GetInstance().Update();

	// 削除処理
	SceneBase::Sweep();

#ifdef _DEBUG	
	DebugUpdate();
#endif 
}

void SceneGame::NormalDraw()
{	
	// 基底クラスの処理
	SceneBase::NormalDraw();
	if (gameStart_) { gameStart_->Draw(); }

#ifdef _DEBUG
	// デバッグ用の情報描画
	//DebugDraw();
#endif
}

void SceneGame::UpdateGameStart()
{
	gameStart_->Update();
	if (gameStart_->IsEnd())
	{
		gameStart_ = nullptr;
		gameUpdate_ = std::bind(&SceneGame::UpdateGameMain, this);
	}
}

void SceneGame::UpdateGameMain()
{
}

void SceneGame::DebugUpdate()
{
	// シーン遷移
	if (inputMng_.IsTrgDown(InputManager::TYPE::DEBUG_SCENE_CHANGE))
	{
		scnMng_.ChangeScene(SceneManager::SCENE_ID::BOSS);
		return;
	}

	// カメラモード切替
	switch (mainCamera.GetMode())
	{
		case Camera::MODE::FREE:
		if (inputMng_.IsTrgDown(InputManager::TYPE::DEBUG_CAMERA_CHANGE))
		{
			mainCamera.ChangeMode(Camera::MODE::FIXED_POINT);
		}
		break;

		case Camera::MODE::FIXED_POINT:
		if (inputMng_.IsTrgDown(InputManager::TYPE::DEBUG_CAMERA_CHANGE))
		{
			mainCamera.ChangeMode(Camera::MODE::PLAYER_FOLLOW);
		}
		break;

		case Camera::MODE::PLAYER_FOLLOW:
		if (inputMng_.IsTrgDown(InputManager::TYPE::DEBUG_CAMERA_CHANGE))
		{
			mainCamera.ChangeMode(Camera::MODE::FREE);
		}
		break;

		default:
		break;
	}
}

void SceneGame::DebugDraw()
{
	// 基底クラスの描画処理
	SceneBase::DebugDraw();

	constexpr int INIT_POS_Y = 60;
	constexpr int OFFSET_Y = 20;
	int posY = INIT_POS_Y;
	
	// カメラ位置
	Vector2F cPosF = mainCamera.GetPos();
	Vector2F pPos = PlayerManager::GetInstance().GetCameraFollowPos();
	Vector2F triggerPos = stageMng_.GetEventTriggerPositions().front();

	// 描画
	//DrawFormatString(0, posY, UtilityCommon::RED, L"カメラ位置：%2f,%2f", cPosF.x, cPosF.y);
	//posY += OFFSET_Y;
	//DrawFormatString(0, posY, UtilityCommon::RED, L"プレイヤー位置：%2f,%2f", pPos.x, pPos.y);
	//posY += OFFSET_Y;
	//DrawFormatString(0, posY, UtilityCommon::RED, L"トリガー位置：%2f,%2f", triggerPos.x, triggerPos.y);
	//posY += OFFSET_Y;
	//DrawFormatString(0, posY, UtilityCommon::RED, L"テスト：%2f,%2f", triggerPos.x + cPosF.x, triggerPos.y + cPosF.y);
	Vector2 cPos = cPosF.ToVector2();

	for (auto& pos : stageMng_.GetEventTriggerPositions())
	{
		DrawCircle(
			pos.x + cPos.x,
			pos.y + cPos.y,
			3.0f,
			UtilityCommon::RED,
			true);
	}
}