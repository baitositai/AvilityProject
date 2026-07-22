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
#include "ScenePause.h"
#include "SceneBoss.h"

SceneBoss::SceneBoss()
{
	// 更新関数のセット
	updataFunc_ = std::bind(&SceneBoss::LoadingUpdate, this);

	// 描画関数のセット
	drawFunc_ = std::bind(&SceneBoss::LoadingDraw, this);

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

	// 基底クラスの初期化処理
	SceneBase::Init();	

	// 敵の更新を戻す
	enemyMng_.SetIsStop(false);
	
	// プレイヤーの初期位置を決定
	playerMng_.SetFirstPositions(stageMng_.GetPlayerFirstPositions());

	// サウンド再生
	sndMng_.PlayBgm(SoundType::BOSS_SOUND_MAP.at(bossType_));

	// UI作成
	uiMng_.CreateGameUi();
}

void SceneBoss::NormalUpdate()
{
	SceneBase::NormalUpdate();

	// ボスを撃破できた場合
	if (enemyMng_.IsBossDestroy(bossType_))
	{
		sndMng_.StopBgm(SoundType::BGM::GAME2);
		scnMng_.ChangeScene(SceneManager::SCENE_ID::RESULT);
		return;
	}

#ifdef _DEBUG
	// デバッグ用の更新処理
	//DebugUpdate();
#endif
}

void SceneBoss::NormalDraw()
{
	SceneBase::NormalDraw();

#ifdef _DEBUG
	// デバッグ用の情報描画
	//DebugDraw();
#endif
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