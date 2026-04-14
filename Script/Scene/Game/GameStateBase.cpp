#include "../../Manager/Common/Camera.h"
#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Game/CollisionManager.h"
#include "../../Manager/Game/EnemyManager.h"
#include "../../Manager/Game/PlayerManager.h"
#include "../../Object/Stage/Stage.h"
#include "GameStateBase.h"

GameStateBase::GameStateBase(Stage& stage) :
	playerMng_(PlayerManager::GetInstance()),
	enemyMng_(EnemyManager::GetInstance()),
	collisionMng_(CollisionManager::GetInstance()),
	stage_(stage)
{
}

GameStateBase::~GameStateBase()
{
}

void GameStateBase::Init()
{
	// ƒJƒƒ‰‚ÌˆÚ“®§ŒÀ‚ğİ’è
	Vector2 stageSize = stage_.GetStageSize();
	mainCamera.SetCameraLimit(Vector2F{0.0f, 0.0f}, stageSize.ToVector2F());
}

void GameStateBase::Update()
{
	playerMng_.Update();
	enemyMng_.Update();
	collisionMng_.Update();
	stage_.Update();
}

void GameStateBase::Draw()
{
	playerMng_.Draw();
	enemyMng_.Draw();
	stage_.Draw();
}

void GameStateBase::DebugDraw()
{
	playerMng_.DebugDraw();
	enemyMng_.DebugDraw();
	collisionMng_.DebugDraw();
	stage_.DebugDraw();
}