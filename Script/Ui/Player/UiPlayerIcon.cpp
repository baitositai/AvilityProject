#include <DxLib.h>
#include "../../Application.h"
#include "../../Object/Character/Player.h"
#include "../../Manager/Common/ResourceManager.h"
#include "UiPlayerIcon.h"

UiPlayerIcon::UiPlayerIcon(const Player& owner) :
	UiPlayerBase(owner)
{
}

UiPlayerIcon::~UiPlayerIcon()
{
}

void UiPlayerIcon::Init()
{
	// 初期化処理
	UiPlayerBase::Init();	

	// 相対位置
	Vector2 localPos = { -176, 5 };

	// 描画位置の設定
	pos_ = Vector2::AddVector2(basePos_, localPos);

	// リソース取得
	int* handles = resourceManager_.GetHandles("playerIcons");
	handle_ = handles[playerNum_];
}

void UiPlayerIcon::Update()
{
	// プレイヤーの活動状況に応じて活動状態を変更
	isActive_ = owner_.IsActive();
}