#include <DxLib.h>
#include "../Application.h"
#include "../Manager/Common/SceneManager.h"
#include "../Manager/Common/Camera.h"
#include "../Manager/Common/InputManager.h"
#include "../Manager/Game/GameManager.h"
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
	FactoryComponent::CreateInstance();
	GameManager::CreateInstance();
}

SceneGame::~SceneGame()
{
	// 管理クラスの解放
	GameManager::GetInstance().Destroy();
	FactoryComponent::GetInstance().Destroy();
}

void SceneGame::Init()
{
	// カメラ設定
	mainCamera.ChangeMode(Camera::MODE::FIXED_POINT); 

	// 管理クラスの初期化
	GameManager::GetInstance().Init();
}

void SceneGame::NormalUpdate()
{
	// ポーズ画面
	//if (inputMng_.IsTrgDown(InputManager::TYPE::PAUSE))
	//{
	//	scnMng_.PushScene(ScenePause_);
	//	return;
	//}

	// 管理クラスの更新
	GameManager::GetInstance().Update();

#ifdef _DEBUG	

	DebugUpdate();

#endif 
}

void SceneGame::NormalDraw()
{	
	// 管理クラスの描画
	GameManager::GetInstance().Draw();

#ifdef _DEBUG
	// デバッグ用の当たり判定描画
	GameManager::GetInstance().DebugDraw();

	// デバッグ用の情報描画
	DebugDraw();

#endif
}

void SceneGame::ChangeNormal()
{
	// 処理変更
	updataFunc_ = std::bind(&SceneGame::NormalUpdate, this);
	drawFunc_ = std::bind(&SceneGame::NormalDraw, this);

	//フェードイン開始
	scnMng_.StartFadeIn();
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
	constexpr int INIT_POS_Y = 60;
	constexpr int OFFSET_Y = 20;
	int posY = INIT_POS_Y;
	
	// カメラ位置
	Vector2F cPos = mainCamera.GetPos();

	// 描画
	DrawFormatString(0, posY, UtilityCommon::RED, L"カメラ位置：%2f,%2f", cPos.x, cPos.y);
	posY += OFFSET_Y;
}