#include "../../Manager/Common/ResourceManager.h"
#include "../../Manager/Common/SceneManager.h"
#include "UiPlayerGetItemMessage.h"

UiPlayerGetItemMessage::UiPlayerGetItemMessage(const Player& owner):
	UiPlayerBase(owner),
	drawCnt_()
{
	abilityStr_.emplace(AvilityTypes::TYPE::AIRSLASH, L"エアースラッシュ");
	abilityStr_.emplace(AvilityTypes::TYPE::AIRWALK, L"空中歩行");
	abilityStr_.emplace(AvilityTypes::TYPE::GIANT, L"巨人化");
	abilityStr_.emplace(AvilityTypes::TYPE::GRAVITYCONTROLL, L"重力操作");
	abilityStr_.emplace(AvilityTypes::TYPE::METAL, L"メタル");
	abilityStr_.emplace(AvilityTypes::TYPE::SHOT, L"ショット");
	abilityStr_.emplace(AvilityTypes::TYPE::STAMP, L"スタンプ");
	abilityStr_.emplace(AvilityTypes::TYPE::SUPERMAN, L"スーパーマン");
	abilityStr_.emplace(AvilityTypes::TYPE::TELEPORT, L"テレポート");
}

UiPlayerGetItemMessage::~UiPlayerGetItemMessage()
{
}

void UiPlayerGetItemMessage::Init()
{
	drawCnt_ = 3.0f;
	handle_ = resourceManager_.GetHandle("fontKinkakuji");
	characterString_.fontHandle = handle_;
}

void UiPlayerGetItemMessage::Update()
{
	if (drawCnt_ < 0)
	{
		isDelete_ = true;
		drawCnt_ = 0.0f;
		isActive_ = false;
		return;
	}
	drawCnt_ -= SceneManager::GetInstance().GetDeltaTime();
}

void UiPlayerGetItemMessage::Draw()
{
	if (isActive_)
	{
		characterString_.DrawCenter();
	}
}

void UiPlayerGetItemMessage::AddAvilityMessage(const AvilityTypes::TYPE& getAvilitytype)
{
	characterString_.string = abilityStr_[getAvilitytype] + GET_AVILITY_MESSAGE_COMMON;
}
