#include <DxLib.h>
#include <string>
#include "../Manager/Common/SceneManager.h"
#include "../Manager/Common/InputManager.h"
#include "../Manager/Common/ResourceManager.h"
#include "../Manager/Common/FontManager.h"
#include "../Manager/Common/SoundManager.h"
#include "../Manager/Common/SpriteEffectManager.h"
#include "../Manager/Game/CollisionManager.h"
#include "../Manager/Game/PlayerManager.h"
#include "../Manager/Game/GimmickManager.h"
#include "../Manager/Game/EnemyManager.h"
#include "../Manager/Game/ItemManager.h"
#include "../Manager/Game/StageManager.h"
#include "../Factory/FactoryComponent.h"
#include "../Common/Loading.h"
#include "../Utility/UtilityCommon.h"
#include "SceneBase.h"

SceneBase::SceneBase() :
	resMng_(ResourceManager::GetInstance()),
	scnMng_(SceneManager::GetInstance()),
	inputMng_(InputManager::GetInstance()),
	fontMng_(FontManager::GetInstance()),
	sndMng_(SoundManager::GetInstance()),
	loading_(Loading::GetInstance()),
	playerMng_(PlayerManager::GetInstance()),
	enemyMng_(EnemyManager::GetInstance()),
	collisionMng_(CollisionManager::GetInstance()),
	stageMng_(StageManager::GetInstance()),
	itemMng_(ItemManager::GetInstance()),
	gimmickMng_(GimmickManager::GetInstance()),
	effectMng_(SpriteEffectManager::GetInstance()),
	facCom_(FactoryComponent::GetInstance())
{
	//// 更新関数のセット
	//updataFunc_ = std::bind(&SceneBase::LoadingUpdate, this);

	//// 描画関数のセット
	//drawFunc_ = std::bind(&SceneBase::LoadingDraw, this);
}

SceneBase::~SceneBase()
{
}

void SceneBase::Load()
{
	// 非同期読み込み開始
	loading_.StartASyncLoad();
	
	// シーン内のリソースを読み込む
	resMng_.SceneChangeResource(static_cast<int>(scnMng_.GetSceneID()));
}

void SceneBase::Init()
{
	// 各種オブジェクトらの初期化
	stageMng_.Init();
	playerMng_.Init();
	enemyMng_.Init();
	collisionMng_.Init();
	itemMng_.Init();
	gimmickMng_.Init();
}

void SceneBase::Update()
{
	updataFunc_();
}

void SceneBase::Draw()
{
	drawFunc_();
}

void SceneBase::LoadingUpdate()
{
	// ローディング中の場合
	if (loading_.IsLoading())
	{
		// ローディング中の更新処理
		loading_.Update();
		return;
	}

	// サウンドのリソースの切り替え
	sndMng_.SceneChangeResources();

	// 初期化
	Init();

	// 処理の変更
	ChangeNormal();

	//フェードイン開始
	scnMng_.StartFadeIn();
}

void SceneBase::NormalUpdate()
{
	// 更新処理
	playerMng_.Update();
	enemyMng_.Update();
	stageMng_.Update();
	itemMng_.Update();
	gimmickMng_.Update();
	effectMng_.Update();
	collisionMng_.Update();

	// 削除処理
	enemyMng_.Sweep();
	itemMng_.Sweep();
	collisionMng_.Sweep();
	effectMng_.Sweep();
	gimmickMng_.Sweep();
}

void SceneBase::LoadingDraw()
{
	// ローディング画面の描画
	loading_.Draw();
}

void SceneBase::NormalDraw()
{
	stageMng_.Draw();
	gimmickMng_.Draw();
	playerMng_.Draw();
	enemyMng_.Draw();
	effectMng_.Draw();
}

void SceneBase::ChangeNormal()
{
	// 更新関数のセット
	updataFunc_ = std::bind(&SceneBase::NormalUpdate, this);

	// 描画関数のセット
	drawFunc_ = std::bind(&SceneBase::NormalDraw, this);
}

void SceneBase::DebugUpdate()
{
}

void SceneBase::DebugDraw()
{
	stageMng_.DebugDraw();
	gimmickMng_.DebugDraw();
	playerMng_.DebugDraw();
	enemyMng_.DebugDraw();
	itemMng_.DebugDraw();
	effectMng_.DebugDraw();
	collisionMng_.DebugDraw();
}
