#include "../../Scene/Game/GameStateBoss.h"
#include "../../Scene/Game/GameStateRoad.h"
#include "../../Scene/Game/GameStateEvent.h"
#include "../Common/SceneManager.h"
#include "CollisionManager.h"
#include "StageManager.h"
#include "PlayerManager.h"
#include "EnemyManager.h"
#include "ItemManager.h"
#include "GameManager.h"

void GameManager::Init()
{	
	// 各種オブジェクトらの初期化
	StageManager::GetInstance().Init();
	PlayerManager::GetInstance().Init();
	EnemyManager::GetInstance().Init();
	CollisionManager::GetInstance().Init();	
	ItemManager::GetInstance().Init();

	// 各種状態別処理の作成
	gameStateMap_.emplace(STATE::ROAD, std::move(std::make_unique<GameStateRoad>()));
	gameStateMap_.emplace(STATE::BOSS, std::move(std::make_unique<GameStateBoss>()));

	// 初期状態の設定
	ChangeState(STATE::ROAD);
}

void GameManager::Update()
{
	// 各種ゲーム状態の更新
	gameStateMap_.at(state_)->Update();
}

void GameManager::Draw()
{
	// 各種ゲーム状態の描画
	gameStateMap_.at(state_)->Draw();
}

void GameManager::ChangeState(const STATE state)
{
	// 状態の変更
	state_ = state;

	// 状態遷移の関数マップの初期化
	changeStateMap_[state]();

	// 状態遷移後の初期化
	gameStateMap_.at(state_)->Init();
}

void GameManager::DebugDraw()
{
	// 各種ゲーム状態のデバッグ描画
	gameStateMap_.at(state_)->DebugDraw();
}

void GameManager::GameOver()
{
	// シーン遷移	
	SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAMEOVER);
}

void GameManager::ChangeStateRoad()
{
}

void GameManager::ChangeStateBoss()
{
}

void GameManager::ChangeStateEvent()
{
}

GameManager::GameManager()
{
	// 初期化
	state_ = STATE::MAX;

	// 各種オブジェクトらの生成
	StageManager::CreateInstance();
	PlayerManager::CreateInstance();
	EnemyManager::CreateInstance();
	CollisionManager::CreateInstance();
	ItemManager::CreateInstance();

	// 状態遷移の関数マップの初期化
	changeStateMap_[STATE::ROAD] = std::bind(&GameManager::ChangeStateRoad, this);
	changeStateMap_[STATE::BOSS] = std::bind(&GameManager::ChangeStateBoss, this);
	changeStateMap_[STATE::EVENT] = std::bind(&GameManager::ChangeStateEvent, this);
}

GameManager::~GameManager()
{
	StageManager::GetInstance().Destroy();
	PlayerManager::GetInstance().Destroy();
	EnemyManager::GetInstance().Destroy();
	CollisionManager::GetInstance().Destroy();
	ItemManager::GetInstance().Destroy();
}
