#include <DxLib.h>
#include "../Application.h"
#include "../Manager/Common/SceneManager.h"
#include "../Manager/Common/Camera.h"
#include "../Manager/Common/InputManager.h"
#include "../Manager/Common/SpriteEffectManager.h"
#include "../Manager/Game/GameManager.h"
#include "../Manager/Game/PlayerManager.h"
#include "../Manager/Game/CollisionManager.h"
#include "../Manager/Game/EnemyManager.h"
#include "../Manager/Game/StageManager.h"
#include "../Manager/Game/ItemManager.h"
#include "../Factory/FactoryComponent.h"
#include "../Utility/UtilityCommon.h"
#include "ScenePause.h"
#include "SceneBoss.h"

SceneBoss::SceneBoss()
{
	// 更新関数のセット
	updataFunc_ = std::bind(&SceneBoss::LoadingUpdate, this);

	// 描画関数のセット
	drawFunc_ = std::bind(&SceneBoss::LoadingDraw, this);
}

SceneBoss::~SceneBoss()
{
}

void SceneBoss::Init()
{	
	// ボス部屋の生成
	stageMng_.Create(StageManager::TYPE::BOSS);

	// 敵を削除
	enemyMng_.Clear();

	// カメラ設定
	mainCamera.ChangeMode(Camera::MODE::FIXED_POINT);
	mainCamera.SetCameraPos(Vector2F(0.0f, 0.0f));

	// 基底クラスの初期化処理
	SceneBase::Init();	
	
	// プレイヤーの初期位置を決定
	playerMng_.SetFirstPositions(stageMng_.GetPlayerFirstPositions());
}

void SceneBoss::NormalUpdate()
{
	SceneBase::NormalUpdate();
}

void SceneBoss::NormalDraw()
{
	SceneBase::NormalDraw();
}

void SceneBoss::DebugUpdate()
{
	SceneBase::DebugUpdate();
}

void SceneBoss::DebugDraw()
{
	SceneBase::DebugDraw();
}