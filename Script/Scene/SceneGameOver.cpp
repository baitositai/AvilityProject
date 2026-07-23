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

	pleaseButton_.handleId = resMng_.GetHandle("pleaseButton");
	pleaseButton_.pos = { Application::SCREEN_HALF_X, Application::SCREEN_HALF_Y + 170 };
}

void SceneGameOver::NormalUpdate()
{
	// シーン遷移
	if (inputMng_.IsTrgDown(InputManager::TYPE::SCENE_CHANGE))
	{
		scnMng_.ChangeScene(SceneManager::SCENE_ID::TITLE);
		sndMng_.StopBgm(SoundType::BGM::RESULT);
		playerMng_.AllDetachItem();
		playerMng_.Clear();
		itemMng_.SetAllIsCarry(false);
		return;
	}
}

void SceneGameOver::NormalDraw()
{
	backGround_.DrawExtend();

	// 点滅の1周期にかかる時間
	constexpr int BLINK_CYCLE_MS = 3200;

	// 現在の時間を取得
	int nowTime = GetNowCount();

	// 周期に基づいて角度を計算
	float currentAngle = (nowTime % BLINK_CYCLE_MS) * DX_PI_F * 2.0f / static_cast<float>(BLINK_CYCLE_MS);

	// サイン波を使って範囲変換
	int alphaValue = static_cast<int>((sin(currentAngle) + 1.0f) * (UtilityCommon::ALPHA_MAX / 2.0f));

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alphaValue);
	pleaseButton_.DrawRota();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}