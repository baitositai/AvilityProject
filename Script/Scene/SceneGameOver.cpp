#include <DxLib.h>
#include "../Application.h"
#include "../Manager/Common/SceneManager.h"
#include "../Manager/Common/InputManager.h"
#include "../Manager/Common/ResourceManager.h"
#include "../Manager/Common/SoundManager.h"
#include "../Manager/Common/FontManager.h"
#include "../Manager/Common/ScoreManager.h"
#include "../Render/PixelMaterial.h"
#include "../Render/PixelRenderer.h"
#include "../Utility/UtilityCommon.h"
#include "SceneGameOver.h"

SceneGameOver::SceneGameOver()
{
}

SceneGameOver::~SceneGameOver()
{
}

void SceneGameOver::Init()
{
}

void SceneGameOver::NormalUpdate()
{
	// ÉVÅ[ÉìëJà⁄
	if (inputMng_.IsTrgDown(InputManager::TYPE::DEBUG_SCENE_CHANGE))
	{
		scnMng_.ChangeScene(SceneManager::SCENE_ID::TITLE);
		sndMng_.StopBgm(SoundType::BGM::RESULT);
		return;
	}
}

void SceneGameOver::NormalDraw()
{
	DrawFormatString(0, 0, UtilityCommon::WHITE, L"GAME OVER", true);
}

void SceneGameOver::ChangeNormal()
{
}
