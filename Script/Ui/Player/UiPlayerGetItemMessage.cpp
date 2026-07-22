#include <DxLib.h>
#include "../../Utility/UtilityCommon.h"
#include "../../Manager/Common/ResourceManager.h"
#include "../../Manager/Common/FontManager.h"
#include "../../Manager/Common/SceneManager.h"
#include "../Object/Character/Player.h"
#include "UiPlayerGetItemMessage.h"

UiPlayerGetItemMessage::UiPlayerGetItemMessage(const Player& owner, const TYPE type) :
	UiPlayerBase(owner),
	type_(type)
{	
	abilityType_ = AvilityTypes::TYPE::MAX;
	alpha_ = 0.0f;
	power_ = -1;
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
	alpha_ = UtilityCommon::ALPHA_MAX;
	const std::wstring fontName = resourceManager_.GetFontName("fontKinkakuji");
	characterString_.fontHandle = FontManager::GetInstance().CreateMyFont(fontName, 32, 1);
	characterString_.color = TEXT_COLOR[static_cast<int>(owner_.GetParameter().padNo_) - 1];

	// プレイヤー頭部の位置を取得
	characterString_.pos = owner_.GetItemMessageDisplayPos();

	switch (type_)
	{
	case TYPE::ABILITY:
		characterString_.string = abilityStr_[abilityType_] + GET_AVILITY_MESSAGE_COMMON;
		break;

	case TYPE::ATTACK_UP:
		characterString_.string = L"攻撃力が%dになりました";
		characterString_.data1 = power_;
		break;

	case TYPE::SPEED_UP:
		characterString_.string = L"移動速度が上がりました";
		break;

	case TYPE::LIFE_UP:
		characterString_.string = L"最大HPが%dになりました";
		characterString_.data1 = power_;
		break;
	}
}

void UiPlayerGetItemMessage::Update()
{
	// アルファ値の更新
	alpha_ -= ALPHA_SPEED;
	if (alpha_ < 0.0f)
	{
		// 削除処理
		Delete();
		return;
	}

	// 上方向に少し移動
	characterString_.pos.y -= MOVE_SPEED;
}

void UiPlayerGetItemMessage::Draw()
{
	if (isActive_)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)alpha_);
		characterString_.DrawFormatCenter();		
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}