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
#include "SceneResult.h"

SceneResult::SceneResult()
{
	// 更新関数のセット
	updataFunc_ = std::bind(&SceneResult::LoadingUpdate, this);

	// 描画関数のセット
	drawFunc_ = std::bind(&SceneResult::LoadingDraw, this);
}

SceneResult::~SceneResult()
{
}

void SceneResult::Init()
{
	backGround_.handleId = resMng_.GetHandle("gameClear");
	backGround_.size = { Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y };
	// フォント
	scoreText_.fontHandle = fontMng_.CreateMyFont(L"ベストテンDOT", 48, 3);
	scoreText_.data1 = scoreManager_.GetScore();
	scoreText_.string = L"盗んだ金額は%dでした";
	scoreText_.pos = { Application::SCREEN_HALF_X, 280 };
	scoreText_.color = UtilityCommon::WHITE;

	sndMng_.PlayBgm(SoundType::BGM::RESULT);
}

void SceneResult::NormalUpdate()
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

void SceneResult::NormalDraw()
{
	backGround_.DrawExtend();
	scoreText_.DrawFormatCenter();
}