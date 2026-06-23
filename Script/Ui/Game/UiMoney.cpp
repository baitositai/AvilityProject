#include "../../Manager/Common/ResourceManager.h"
#include "../../Manager/Common/ScoreManager.h"
#include "../../Manager/Common/SceneManager.h"
#include "UiMoney.h"

UiMoney::UiMoney() :
	scoreManager_(ScoreManager::GetInstance()),
	sceneManager_(SceneManager::GetInstance())
{
}

UiMoney::~UiMoney()
{
}

void UiMoney::Init()
{
	// 初期化処理
	UiBase::Init();

	// 描画位置の設定
	pos_ = { 190, 72 };

	// リソース取得
	int* handles = resourceManager_.GetHandles("gameStatusUis");
	handle_ = handles[1];

	// 初期化処理
	InitNumber();
}

void UiMoney::Update()
{
	if (sceneManager_.GetSceneID() == SceneManager::SCENE_ID::TRAIN)
	{
		drawCount_ = scoreManager_.GetTotalScore();
	}
	else
	{
		drawCount_ = scoreManager_.GetScore();
	}
}

void UiMoney::Draw()
{
	// 描画処理
	UiGameBase::Draw();
}
