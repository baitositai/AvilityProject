#include "../../Scene/Game/GameStateBoss.h"
#include "../../Scene/Game/GameStateRoad.h"
#include "../../Scene/Game/GameStateEvent.h"
#include "../Object/Stage/Stage.h"
#include "CollisionManager.h"
#include "PlayerManager.h"
#include "EnemyManager.h"
#include "GameManager.h"

void GameManager::Init()
{
	stage_->Init();
	PlayerManager::GetInstance().Init();
	EnemyManager::GetInstance().Init();
	CollisionManager::GetInstance().Init();
}

void GameManager::Update()
{
	gameStateList_.front()->Update();
}

void GameManager::Draw()
{

}

void GameManager::DebugDraw()
{

}

GameManager::GameManager()
{
	stage_ = std::make_unique<Stage>();
	PlayerManager::CreateInstance();
	EnemyManager::CreateInstance();
	CollisionManager::CreateInstance();
}

GameManager::~GameManager()
{
}
