#include "../../Manager/Common/Camera.h"
#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Common/SpriteEffectManager.h"
#include "../../Manager/Game/CollisionManager.h"
#include "../../Manager/Game/EnemyManager.h"
#include "../../Manager/Game/PlayerManager.h"
#include "../../Manager/Game/StageManager.h"
#include "../../Manager/Game/ItemManager.h"
#include "GameStateBoss.h"

GameStateBoss::GameStateBoss()
{
}

GameStateBoss::~GameStateBoss()
{
}

void GameStateBoss::Init()
{
	// カメラ設定
	mainCamera.ChangeMode(Camera::MODE::FIXED_POINT);

	// ステージの変更
	stageMng_.ChageStage(StageManager::TYPE::BOSS);

	// プレイヤーの初期位置を決定
	playerMng_.SetFirstPositions(stageMng_.GetMapChipIndexPositions(-10001));
}