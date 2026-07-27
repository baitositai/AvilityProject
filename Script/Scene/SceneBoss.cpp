#include <DxLib.h>
#include "../Application.h"
#include "../Manager/Common/SceneManager.h"
#include "../Manager/Common/Camera.h"
#include "../Manager/Common/InputManager.h"
#include "../Manager/Common/SoundManager.h"
#include "../Manager/Common/SpriteEffectManager.h"
#include "../Manager/Common/ScoreManager.h"
#include "../Manager/Game/GameManager.h"
#include "../Manager/Game/PlayerManager.h"
#include "../Manager/Game/GimmickManager.h"
#include "../Manager/Game/CollisionManager.h"
#include "../Manager/Game/EnemyManager.h"
#include "../Manager/Game/StageManager.h"
#include "../Manager/Game/ItemManager.h"
#include "../Manager/Game/UiManager.h"
#include "../Factory/FactoryComponent.h"
#include "../Utility/UtilityCommon.h"
#include "../System/GameStart.h"
#include "ScenePause.h"
#include "SceneBoss.h"

SceneBoss::SceneBoss()
{
	// 処理の登録
	updataFunc_ = std::bind(&SceneBoss::LoadingUpdate, this);
	drawFunc_ = std::bind(&SceneBoss::LoadingDraw, this);		
	gameUpdate_ = std::bind(&SceneBoss::UpdateGameStart, this);

	// 初期化
	bossType_ = EnemyTypes::TYPE::MAX;
}

SceneBoss::~SceneBoss()
{
	//sndMng_.StopBgm(SoundType::BOSS_SOUND_MAP.at(bossType_));
}

void SceneBoss::Init()
{		
	// ボス指定
	bossType_ = enemyMng_.GetBossEnemyType();

	// ボス部屋の生成
	stageMng_.Create(StageManager::TYPE::BOSS);

	// ボス生成
	enemyMng_.Create(bossType_, Vector2F(1050, 500));

	// カメラ設定
	mainCamera.ChangeMode(Camera::MODE::FIXED_POINT);
	mainCamera.SetCameraPos(Vector2F(0.0f, 0.0f));

	// 各種オブジェクトらの初期化
	stageMng_.Init();
	playerMng_.Init();
	enemyMng_.Init();
	collisionMng_.Init();
	gimmickMng_.Init();
	uiMng_.Init();

	// 敵の更新を戻す
	enemyMng_.SetIsStop(false);
	
	// プレイヤーの初期位置を決定
	playerMng_.SetFirstPositions(stageMng_.GetPlayerFirstPositions());

	// サウンド再生
	sndMng_.PlayBgm(SoundType::BOSS_SOUND_MAP.at(bossType_));

	// UI作成
	uiMng_.CreateGameUi();

	// プレイヤーが持つアイテムを追従するためアイテムのみ初期化
	itemMng_.Init();

	// ゲーム開始処理
	gameStart_ = std::make_unique<GameStart>(1);
	gameStart_->Init();

	sceneChangeTimer_ = SCENE_CHANGE_DELAY;
	isSceneChanges_ = false;
}

void SceneBoss::NormalUpdate()
{
	gameUpdate_();
	SceneBase::NormalUpdate();
	SceneBase::Sweep();

	// ボスを撃破できた場合
	if (enemyMng_.IsBossDestroy(bossType_))
	{

		sceneChangeTimer_ -= scnMng_.GetDeltaTime();
		if (sceneChangeTimer_ < 0.0f && !isSceneChanges_)
		{
			isSceneChanges_ = true;
			sndMng_.StopBgm(SoundType::BGM::GAME2);
			scnMng_.ChangeScene(SceneManager::SCENE_ID::RESULT);
			return;
		}
	}

#ifdef _DEBUG
	// デバッグ用の更新処理
	DebugUpdate();
#endif
}

void SceneBoss::NormalDraw()
{
	SceneBase::NormalDraw();
	if (gameStart_) { gameStart_->Draw(); }
#ifdef _DEBUG
	// デバッグ用の情報描画
	//DebugDraw();
#endif
}

void SceneBoss::UpdateGameStart()
{
	gameStart_->Update();
	if (gameStart_->IsEnd())
	{
		gameStart_ = nullptr;
		gameUpdate_ = std::bind(&SceneBoss::UpdateGameMain, this);
	}
}

void SceneBoss::UpdateGameMain()
{
}

void SceneBoss::DebugUpdate()
{
	SceneBase::DebugUpdate();

	// シーン遷移
	if (inputMng_.IsTrgDown(InputManager::TYPE::DEBUG_SCENE_CHANGE))
	{
		scnMng_.ChangeScene(SceneManager::SCENE_ID::RESULT);
		return;
	}
}

void SceneBoss::DebugDraw()
{
	SceneBase::DebugDraw();
}