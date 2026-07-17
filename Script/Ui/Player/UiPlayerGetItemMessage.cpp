#include "../../Utility/UtilityCommon.h"
#include "../../Manager/Common/ResourceManager.h"
#include "../../Manager/Common/FontManager.h"
#include "../../Manager/Common/SceneManager.h"
#include "../Object/Character/Player.h"
#include "UiPlayerGetItemMessage.h"

UiPlayerGetItemMessage::UiPlayerGetItemMessage(const Player& owner, const AvilityTypes::TYPE& getAvilitytype):
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

	characterString_.string = abilityStr_[getAvilitytype] + GET_AVILITY_MESSAGE_COMMON;
}

UiPlayerGetItemMessage::~UiPlayerGetItemMessage()
{
}

void UiPlayerGetItemMessage::Init()
{
	drawCnt_ = 5.0f;
	const std::wstring fontName = resourceManager_.GetFontName("fontKinkakuji");
	characterString_.fontHandle = FontManager::GetInstance().CreateMyFont(fontName, 32, 1);
	characterString_.color = UtilityCommon::WHITE;
	characterString_.pos = owner_.GetParameter().drawPos_;
}

void UiPlayerGetItemMessage::Update()
{
	if (drawCnt_ < 0.0f)
	{
		isDelete_ = true;
		drawCnt_ = 0.0f;
		isActive_ = false;
		return;
	}
	drawCnt_ -= SceneManager::GetInstance().GetDeltaTime();
	characterString_.pos = owner_.GetParameter().drawPos_;
}

void UiPlayerGetItemMessage::Draw()
{
	if (isActive_)
	{
		characterString_.DrawCenter();
	}
}
