#include "../../Manager/Common/Camera.h"
#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Game/CollisionManager.h"
#include "../../Manager/Game/EnemyManager.h"
#include "../../Manager/Game/PlayerManager.h"
#include "../../Manager/Game/StageManager.h"
#include "GameStateBase.h"

GameStateBase::GameStateBase() :
	playerMng_(PlayerManager::GetInstance()),
	enemyMng_(EnemyManager::GetInstance()),
	collisionMng_(CollisionManager::GetInstance()),
	stageMng_(StageManager::GetInstance())
{
}

GameStateBase::~GameStateBase()
{
}

void GameStateBase::Init()
{
	// ƒJƒƒ‰‚ÌˆÚ“®§ŒÀ‚ğİ’è
	Vector2 stageSize = stageMng_.GetStageSize();
	mainCamera.SetCameraLimit(Vector2F{0.0f, 0.0f}, stageSize.ToVector2F());
}

void GameStateBase::Update()
{
	playerMng_.Update();
	enemyMng_.Update();	
	stageMng_.Update();
	collisionMng_.Update();
}

void GameStateBase::Draw()
{	
	stageMng_.Draw();
	playerMng_.Draw();
	enemyMng_.Draw();
}

void GameStateBase::DebugDraw()
{	
	stageMng_.DebugDraw();
	playerMng_.DebugDraw();
	enemyMng_.DebugDraw();
	collisionMng_.DebugDraw();
}