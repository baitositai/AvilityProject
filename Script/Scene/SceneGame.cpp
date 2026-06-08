#include <DxLib.h>
#include "../Application.h"
#include "../Manager/Common/SceneManager.h"
#include "../Manager/Common/Camera.h"
#include "../Manager/Common/InputManager.h"
#include "../Manager/Common/SpriteEffectManager.h"
#include "../Manager/Game/GameManager.h"
#include "../Manager/Game/PlayerManager.h"
#include "../Manager/Game/CollisionManager.h"
#include "../Manager/Game/GimmickManager.h"
#include "../Manager/Game/EnemyManager.h"
#include "../Manager/Game/StageManager.h"
#include "../Manager/Game/ItemManager.h"
#include "../Factory/FactoryComponent.h"
#include "../Utility/UtilityCommon.h"
#include "ScenePause.h"
#include "SceneGame.h"

SceneGame::SceneGame()
{
	// 更新関数のセット
	updataFunc_ = std::bind(&SceneGame::LoadingUpdate, this);

	// 描画関数のセット
	drawFunc_ = std::bind(&SceneGame::LoadingDraw, this);

	// 管理クラスの生成
	//GameManager::CreateInstance();
}

SceneGame::~SceneGame()
{
	// 管理クラスの解放
	//GameManager::GetInstance().Destroy();
}

void SceneGame::Init()
{	
	// ステージ生成
	stageMng_.Create(StageManager::TYPE::ROAD);

	// 敵の生成処理
	enemyMng_.Generator(stageMng_.GetEnemyAreaPositions());	

	// ボス部屋の生成
	gimmickMng_.SetBossDoor(stageMng_.GetBossDoorPos());
	
	// 基底クラスの処理
	SceneBase::Init();	
	
	// プレイヤーの初期位置を決定
	playerMng_.SetFirstPositions(stageMng_.GetPlayerFirstPositions());

	// カメラ設定
	mainCamera.ChangeMode(Camera::MODE::CAMERA_SCROLL);

	// カメラの移動制限を設定
	Vector2 stageSize = stageMng_.GetStageSize();
	mainCamera.SetCameraLimit(Vector2F{ 0.0f, 0.0f }, stageSize.ToVector2F());
}

void SceneGame::NormalUpdate()
{
	// ポーズ画面
	//if (inputMng_.IsTrgDown(InputManager::TYPE::PAUSE))
	//{
	//	scnMng_.PushScene(ScenePause_);
	//	return;
	//}

	// 基底クラスの処理
	SceneBase::NormalUpdate();

#ifdef _DEBUG	
	DebugUpdate();
#endif 
}

void SceneGame::NormalDraw()
{	
	// 基底クラスの処理
	SceneBase::NormalDraw();

#ifdef _DEBUG
	// デバッグ用の情報描画
	DebugDraw();
#endif
}

void SceneGame::DebugUpdate()
{
	// シーン遷移
	if (inputMng_.IsTrgDown(InputManager::TYPE::DEBUG_SCENE_CHANGE))
	{
		scnMng_.ChangeScene(SceneManager::SCENE_ID::RESULT);
		return;
	}

	// カメラモード切替
	switch (mainCamera.GetMode())
	{
		case Camera::MODE::FREE:
		if (inputMng_.IsTrgDown(InputManager::TYPE::DEBUG_CAMERA_CHANGE))
		{
			mainCamera.ChangeMode(Camera::MODE::FIXED_POINT);
		}
		break;

		case Camera::MODE::FIXED_POINT:
		if (inputMng_.IsTrgDown(InputManager::TYPE::DEBUG_CAMERA_CHANGE))
		{
			mainCamera.ChangeMode(Camera::MODE::PLAYER_FOLLOW);
		}
		break;

		case Camera::MODE::PLAYER_FOLLOW:
		if (inputMng_.IsTrgDown(InputManager::TYPE::DEBUG_CAMERA_CHANGE))
		{
			mainCamera.ChangeMode(Camera::MODE::FREE);
		}
		break;

		default:
		break;
	}
}

void SceneGame::DebugDraw()
{
	// 基底クラスの描画処理
	SceneBase::DebugDraw();

	constexpr int INIT_POS_Y = 60;
	constexpr int OFFSET_Y = 20;
	int posY = INIT_POS_Y;
	
	// カメラ位置
	Vector2F cPos = mainCamera.GetPos();
	Vector2F pPos = PlayerManager::GetInstance().GetCameraFollowPos();

	// 描画
	DrawFormatString(0, posY, UtilityCommon::RED, L"カメラ位置：%2f,%2f", cPos.x, cPos.y);
	posY += OFFSET_Y;
	DrawFormatString(0, posY, UtilityCommon::RED, L"プレイヤー位置：%2f,%2f", pPos.x, pPos.y);
	posY += OFFSET_Y;
}