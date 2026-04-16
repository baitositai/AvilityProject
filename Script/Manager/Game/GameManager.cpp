#include "../../Scene/Game/GameStateBoss.h"
#include "../../Scene/Game/GameStateRoad.h"
#include "../../Scene/Game/GameStateEvent.h"
#include "CollisionManager.h"
#include "StageManager.h"
#include "PlayerManager.h"
#include "EnemyManager.h"
#include "GameManager.h"

void GameManager::Init()
{
	// 各種オブジェクトらの初期化
	StageManager::GetInstance().Init();
	PlayerManager::GetInstance().Init();
	EnemyManager::GetInstance().Init();
	CollisionManager::GetInstance().Init();

	// 初期状態の設定
	ChangeState(STATE::ROAD);
}

void GameManager::Update()
{
	// 各種ゲーム状態の更新
	game_->Update();
}

void GameManager::Draw()
{
	// 各種ゲーム状態の描画
	game_->Draw();
}

void GameManager::ChangeState(const STATE state)
{
	// 状態の変更
	state_ = state;

	// 状態遷移の関数マップの初期化
	changeStateMap_[state]();

	// 状態遷移後の初期化
	game_->Init();
}

void GameManager::DebugDraw()
{
	// 各種ゲーム状態のデバッグ描画
	game_->DebugDraw();
}

void GameManager::ChangeStateRoad()
{
	game_ = std::make_unique<GameStateRoad>();

	// ステージの変更
	StageManager::GetInstance().ChageStage(StageManager::TYPE::STAGE_FIRST);
}

void GameManager::ChangeStateBoss()
{
	game_ = std::make_unique<GameStateRoad>();
}

void GameManager::ChangeStateEvent()
{
	game_ = std::make_unique<GameStateRoad>();
}

GameManager::GameManager()
{
	// 初期化
	game_ = nullptr;
	state_ = STATE::MAX;

	// 各種オブジェクトらの生成
	StageManager::CreateInstance();
	PlayerManager::CreateInstance();
	EnemyManager::CreateInstance();
	CollisionManager::CreateInstance();

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
}
