#include "../../Manager/Common/Camera.h"
#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Common/SpriteEffectManager.h"
#include "../../Manager/Game/CollisionManager.h"
#include "../../Manager/Game/EnemyManager.h"
#include "../../Manager/Game/PlayerManager.h"
#include "../../Manager/Game/StageManager.h"
#include "../../Manager/Game/ItemManager.h"
#include "GameStateBase.h"

GameStateBase::GameStateBase() :
	playerMng_(PlayerManager::GetInstance()),
	enemyMng_(EnemyManager::GetInstance()),
	collisionMng_(CollisionManager::GetInstance()),
	stageMng_(StageManager::GetInstance()),
	itemMng_(ItemManager::GetInstance()),
	effectMng_(SpriteEffectManager::GetInstance())
{
}

GameStateBase::~GameStateBase()
{
}

void GameStateBase::Init()
{
	// カメラ設定
	mainCamera.ChangeMode(Camera::MODE::CAMERA_SCROLL);
	//mainCamera.SetFollowPos(&playerMng_.GetCameraFollowPos());

	// カメラの移動制限を設定
	Vector2 stageSize = stageMng_.GetStageSize();
	mainCamera.SetCameraLimit(Vector2F{0.0f, 0.0f}, stageSize.ToVector2F());

	// プレイヤーの初期位置を決定
	playerMng_.SetFirstPositions(stageMng_.GetPlayerFirstPositions());

	// 敵の初期位置決定
	enemyMng_.GenerateEnemy();
}

void GameStateBase::Update()
{
	// 更新処理
	playerMng_.Update();
	enemyMng_.Update();	
	stageMng_.Update();	
	itemMng_.Update();
	effectMng_.Update();
	collisionMng_.Update();

	// 削除処理
	enemyMng_.Sweep();
	itemMng_.Sweep();
	collisionMng_.Sweep();
	effectMng_.Sweep();
}

void GameStateBase::Draw()
{	
	stageMng_.Draw();
	playerMng_.Draw();
	enemyMng_.Draw();
	effectMng_.Draw();
}

void GameStateBase::DebugDraw()
{	
	stageMng_.DebugDraw();
	playerMng_.DebugDraw();
	enemyMng_.DebugDraw();
	itemMng_.DebugDraw();
	effectMng_.DebugDraw();
	collisionMng_.DebugDraw();
}