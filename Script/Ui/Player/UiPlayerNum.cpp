#include "../../Object/Character/Player.h"
#include "../../Manager/Common/ResourceManager.h"
#include "UiPlayerNum.h"

UiPlayerNum::UiPlayerNum(const Player& owner):
	UiPlayerBase(owner)
{
	preUiType_ = ParameterPlayer::HEAD_UI::MAX;
	uiChangeMap_.emplace(ParameterPlayer::HEAD_UI::PAD_NO, std::bind(&UiPlayerNum::ChangeResourceUiPadNo, this));
	uiChangeMap_.emplace(ParameterPlayer::HEAD_UI::ENTER_DOOR, std::bind(&UiPlayerNum::ChangeResourceUiEnter, this));
	uiChangeMap_.emplace(ParameterPlayer::HEAD_UI::ITEM_GET, std::bind(&UiPlayerNum::ChangeResourceUiGetItem, this));
	uiChangeMap_.emplace(ParameterPlayer::HEAD_UI::OPEN_TREASURE_CHEST, std::bind(&UiPlayerNum::ChangeResourceUiOpen, this));
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
	pos_ = owner_.GetParameter().drawPos_;
	pos_.y += DRAW_LOCAL_POS_Y;

	// 大きさ
	scale_ = 0.5f;

	// 初期表示リソース
	ChangeResourceUi(ParameterPlayer::HEAD_UI::PAD_NO);
}

void UiPlayerNum::Update()
{
	const auto& parameter = owner_.GetParameter();

	// 所有者が死んでいた場合終了
	if (parameter.hp_<=0)
	{
		isActive_ = false;
		return; 
	}
}

void UiPlayerNum::Draw()
{	
	// UIの変更
	const auto& parameter = owner_.GetParameter();
	ChangeResourceUi(parameter.headUi_);

	// プレイヤーの活動状況に応じて活動状態を変更
	isActive_ = owner_.IsActive();
	pos_ = parameter.drawPos_;
	pos_.y += DRAW_LOCAL_POS_Y;

	// 描画処理
	UiPlayerBase::Draw();
}

void UiPlayerNum::ChangeResourceUi(const ParameterPlayer::HEAD_UI headUiType)
{
	// 同一のものの場合無視
	if (headUiType == preUiType_ || headUiType == ParameterPlayer::HEAD_UI::MAX)
	{
		return;
	}

	// 変更
	preUiType_ = headUiType;
	uiChangeMap_[headUiType]();
}

void UiPlayerNum::ChangeResourceUiPadNo()
{
	// リソース取得
	int* handles = resourceManager_.GetHandles("playerIcons");
	handle_ = handles[playerNum_];
}

void UiPlayerNum::ChangeResourceUiGetItem()
{
	handle_ = resourceManager_.GetHandle("uiGetItem");
}

void UiPlayerNum::ChangeResourceUiEnter()
{
	handle_ = resourceManager_.GetHandle("uiEnter");
}

void UiPlayerNum::ChangeResourceUiOpen()
{
	handle_ = resourceManager_.GetHandle("uiOpen");
}
