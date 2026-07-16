#include "../../Object/Character/Player.h"
#include "../../Manager/Common/ResourceManager.h"
#include "UiPlayerNum.h"

UiPlayerNum::UiPlayerNum(const Player& _owner):
	UiPlayerBase(_owner)
{
}

UiPlayerNum::~UiPlayerNum()
{
}

void UiPlayerNum::Init()
{
	// 初期化処理
	UiPlayerBase::Init();

	//プレイヤーに追従させる
	const ParameterPlayer& ownerParam = owner_.GetParameter();
	Vector2F ownerPos = ownerParam.pos_;
	pos_ = ownerPos.ToVector2();
	pos_.y += DRAW_LOCAL_POS_Y;

	scale_ = 0.5f;

	// リソース取得
	int* handles = resourceManager_.GetHandles("playerIcons");
	handle_ = handles[playerNum_];
}

void UiPlayerNum::Update()
{
	// 所有者が死んでいた場合終了
	if (CheckOwnerDead()) { return; }
	// プレイヤーの活動状況に応じて活動状態を変更
	isActive_ = owner_.IsActive();
	Vector2F ownerPos = owner_.GetParameter().pos_;
	pos_ = ownerPos.ToVector2();
	pos_.y += DRAW_LOCAL_POS_Y;
}
