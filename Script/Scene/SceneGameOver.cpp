#include <DxLib.h>
#include "../Application.h"
#include "../Manager/Common/SceneManager.h"
#include "../Manager/Common/InputManager.h"
#include "../Manager/Common/ResourceManager.h"
#include "../Manager/Common/SoundManager.h"
#include "../Manager/Common/FontManager.h"
#include "../Manager/Common/ScoreManager.h"
#include "../Manager/Game/PlayerManager.h"
#include "../Manager/Game/ItemManager.h"
#include "../Render/PixelMaterial.h"
#include "../Render/PixelRenderer.h"
#include "../Utility/UtilityCommon.h"
#include "SceneGameOver.h"

SceneGameOver::SceneGameOver()
{
	// 更新関数のセット
	updataFunc_ = std::bind(&SceneGameOver::LoadingUpdate, this);

	// 描画関数のセット
	drawFunc_ = std::bind(&SceneGameOver::LoadingDraw, this);
}

SceneGameOver::~SceneGameOver()
{
}

void SceneGameOver::Init()
{
	backGround_.handleId = resMng_.GetHandle("gameOver");
	backGround_.size = { Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y };
	sndMng_.PlayBgm(SoundType::BGM::RESULT);
}

void SceneGameOver::NormalUpdate()
{
	// シーン遷移
	if (inputMng_.IsTrgDown(InputManager::TYPE::SCENE_CHANGE))
	{
		scnMng_.ChangeScene(SceneManager::SCENE_ID::TITLE);
		sndMng_.StopBgm(SoundType::BGM::RESULT);
		playerMng_.AllDetachItem();
		itemMng_.SetAllIsCarry(false);
		return;
	}
}

void SceneGameOver::NormalDraw()
{
	backGround_.DrawExtend();
}