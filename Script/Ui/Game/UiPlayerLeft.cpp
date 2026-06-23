#include "../../Manager/Common/ResourceManager.h"
#include "../../Manager/Game/PlayerManager.h"
#include "UiPlayerLeft.h"

UiPlayerLeft::UiPlayerLeft() :
	playerManager_(PlayerManager::GetInstance())
{
}

UiPlayerLeft::~UiPlayerLeft()
{
}

void UiPlayerLeft::Init()
{
	// 初期化処理
	UiBase::Init();

	// 描画位置の設定
	pos_ = { 190, 24 };

	// リソース取得
	int* handles = resourceManager_.GetHandles("gameStatusUis");
	handle_ = handles[0];

	// 初期化処理
	InitNumber();
}

void UiPlayerLeft::Update()
{
	drawCount_ = playerManager_.GetPlayerLeft();
}

void UiPlayerLeft::Draw()
{
	// 描画処理
	UiGameBase::Draw();
}
