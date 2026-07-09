#include <DxLib.h>
#include "../Application.h"
#include "../Manager/Common/SceneManager.h"
#include "../Manager/Common/Camera.h"
#include "../Manager/Common/InputManager.h"
#include "../Manager/Common/SpriteEffectManager.h"
#include "../Manager/Common/SoundManager.h"
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
#include "SceneTrain.h"

SceneTrain::SceneTrain()
{
	// 更新関数のセット
	updataFunc_ = std::bind(&SceneTrain::LoadingUpdate, this);

	// 描画関数のセット
	drawFunc_ = std::bind(&SceneTrain::LoadingDraw, this);
}

SceneTrain::~SceneTrain()
{
}

void SceneTrain::Init()
{
	// 乗客室の生成
	stageMng_.Create(StageManager::TYPE::TRAIN);

	// カメラ設定
	mainCamera.ChangeMode(Camera::MODE::FIXED_POINT);
	mainCamera.SetCameraPos(Vector2F(0.0f, 0.0f));

	// 基底クラスの初期化処理
	SceneBase::Init();

	// プレイヤーの初期位置を決定
	playerMng_.SetFirstPositions(stageMng_.GetPlayerFirstPositions());

	// BGM再生
	sndMng_.PlayBgm(SoundType::BGM::TRAIN);
	sndMng_.PlayBgm(SoundType::BGM::TRAIN_ROOM);

	// UI作成
	uiMng_.CreateGameUi();

	/// ショップ生成
	//GimmickManager::CreateParameter shop = {};
	//shop.type = GimmickTypes::TYPE::SHOP;
	//shop.pos = Vector2F(970, 577);
	//gimmickMng_.Create(shop);
}

void SceneTrain::SceneChangeReady()
{
	// 全てのアイテムの持越しを禁止
	itemMng_.SetAllIsCarry(false);

	// 全プレイヤーのアイテムをデタッチ
	playerMng_.AllDetachItem();

	// 基底クラスの処理
	SceneBase::SceneChangeReady();
}

void SceneTrain::NormalUpdate()
{
	SceneBase::NormalUpdate();

#ifdef _DEBUG	
	DebugUpdate();
#endif 
}

void SceneTrain::NormalDraw()
{
	SceneBase::NormalDraw();

#ifdef _DEBUG
	// デバッグ用の情報描画
	DebugDraw();
#endif
}

void SceneTrain::DebugUpdate()
{
	SceneBase::DebugUpdate();
}

void SceneTrain::DebugDraw()
{
	SceneBase::DebugDraw();
}