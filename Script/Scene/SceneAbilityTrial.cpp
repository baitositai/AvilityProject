#include <DxLib.h>
#include "../Application.h"
#include "../Manager/Common/SceneManager.h"
#include "../Manager/Common/Camera.h"
#include "../Manager/Common/InputManager.h"
#include "../Manager/Common/SoundManager.h"
#include "../Manager/Common/FontManager.h"
#include "../Manager/Common/SpriteEffectManager.h"
#include "../Manager/Common/ScoreManager.h"
#include "../Manager/Common/ResourceManager.h"
#include "../Manager/Game/GameManager.h"
#include "../Manager/Game/PlayerManager.h"
#include "../Manager/Game/CollisionManager.h"
#include "../Manager/Game/GimmickManager.h"
#include "../Manager/Game/EnemyManager.h"
#include "../Manager/Game/StageManager.h"
#include "../Manager/Game/ItemManager.h"
#include "../Manager/Game/UiManager.h"
#include "../Manager/Game/EventManager.h"
#include "../Factory/FactoryComponent.h"
#include "../Utility/UtilityCommon.h"
#include "SceneAbilityTrial.h"

SceneAbilityTrial::SceneAbilityTrial()
{
	// 処理の登録
	updataFunc_ = std::bind(&SceneAbilityTrial::LoadingUpdate, this);
	drawFunc_ = std::bind(&SceneAbilityTrial::LoadingDraw, this);
}

SceneAbilityTrial::~SceneAbilityTrial()
{
}

void SceneAbilityTrial::Init()
{
	auto& coll = CollisionManager::GetInstance();

	// 乗客室の生成
	stageMng_.Create(StageManager::TYPE::ABILITY_TRIAL);

	// カメラ設定
	mainCamera.ChangeMode(Camera::MODE::FIXED_POINT);
	mainCamera.SetCameraPos(Vector2F(0.0f, 0.0f));

	// 基底クラスの初期化処理
	SceneBase::Init();

	// プレイヤーの初期位置を決定
	playerMng_.SetFirstPositions(stageMng_.GetPlayerFirstPositions());

	// BGM再生
	sndMng_.PlayBgm(SoundType::BGM::TRAIN_ROOM);

	// UI作成
	uiMng_.CreateGameUi();

	// アビリティアイテムの生成
	itemMng_.CreateAbilityTrial(stageMng_.GetItemCreatePositions());

	// サンドバッグの生成
	enemyMng_.CreateSandBagEnemy(stageMng_.GetEnemyAreaPositions().front());
	
}

void SceneAbilityTrial::NormalUpdate()
{
	SceneBase::NormalUpdate();
	itemMng_.CheckAbilityTrial();
	SceneBase::Sweep();

	if (enemyMng_.IsBossDestroy(EnemyTypes::TYPE::GAIA_GOLEM))
	{
		enemyMng_.CreateSandBagEnemy(stageMng_.GetEnemyAreaPositions().front());
	}
}

void SceneAbilityTrial::NormalDraw()
{
	SceneBase::NormalDraw();
}
