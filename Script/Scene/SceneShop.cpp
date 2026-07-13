#include "../Application.h"
#include "../Manager/Common/SceneManager.h"
#include "../Manager/Common/InputManager.h"
#include "../Manager/Common/SoundManager.h"
#include "../Manager/Common/ResourceManager.h"
#include "../Manager/Common/FontManager.h"
#include "../Manager/Common/SpriteEffectManager.h"
#include "../Manager/Common/ScoreManager.h"
#include "../Manager/Game/ItemManager.h"
#include "../Manager/Game/GimmickManager.h"
#include "../Factory/FactoryComponent.h"
#include "../Utility/UtilityCommon.h"
#include "../Render/PixelMaterial.h"
#include "../Render/PixelRenderer.h"
#include "../Object/Stage/BackGround.h"
#include "../Ui/Game/UiMoney.h"
#include "../Component/ComponentTextAnimation.h"
#include "SceneShop.h"

SceneShop::SceneShop()
{
	// 処理の登録
	updataFunc_ = std::bind(&SceneShop::NormalUpdate, this);
	drawFunc_ = std::bind(&SceneShop::NormalDraw, this);

	// 状態遷移登録
	changeStateMap_.emplace(STATE::SELECT, std::bind(&SceneShop::ChangeStateSelect, this));
	changeStateMap_.emplace(STATE::CHECK, std::bind(&SceneShop::ChangeStateCheck, this));

	// 変数初期化
	isPurchase_ = false;
	selectIndex_ = -1;
	arrowHandle_ = -1;
	state_ = STATE::MAX;
	padNo_ = Input::JOYPAD_NO::PAD1;
	frameCount_ = 0.0f;
	exhibits_ = itemMng_.GetRandomExhibits(2,2,2);
}

SceneShop::~SceneShop()
{
}

void SceneShop::Init()
{
	// 背景設定
	float scrollSpeed = -0.5f;
	float addScrollSpeed = -0.2f;
	for (int i = 0; i < BACK_GROUND_NUM - 1; i++)
	{
		backGround_[i] = std::make_unique<BackGround>();
		backGround_[i]->SetType(BackGround::TYPE::SCROLL);
		backGround_[i]->SetScrollSpeed(scrollSpeed);
		backGround_[i]->SetResource("backGround" + std::to_string(i));
		scrollSpeed += addScrollSpeed;
	}

	// 矢印
	arrowHandle_ = resMng_.GetHandle("arrow");

	// 最後の一枚目
	int index = BACK_GROUND_NUM - 1;
	backGround_[index] = std::make_unique<BackGround>();
	backGround_[index]->SetType(BackGround::TYPE::FIX);
	backGround_[index]->SetResource("backGroundShop");

	// 初期状態の指定
	ChangeState(STATE::SELECT);

	// マテリアルとレンダラーの設定
	for (auto& exhibits : exhibits_)
	{
		// 生成
		auto material = std::make_unique<PixelMaterial>(resMng_.GetHandle("standardSprite"), 2);
		material->AddTextureBuf(exhibits.handle);
		material->AddConstBuf(FLOAT4{ 1.0f,1.0f,1.0f,1.0f });
		material->AddConstBuf(FLOAT4{ 1.0f,1.0f,1.0f,1.0f });
		auto renderer = std::make_unique<PixelRenderer>(*material);
		
		// 格納
		exhibitsMaterial_.push_back(std::move(material));
		exhibitsRenderer_.push_back(std::move(renderer));
	}

	// 選択番号初期化
	selectIndex_ = 0;

	// テキスト生成
	message_.fontHandle = fontMng_.CreateMyFont(resMng_.GetFontName("fontDot"), 48, 5);
	message_.pos = { Application::SCREEN_HALF_X, 620 };
	message_.string = TEXT_MAP[TEXT_TYPE::ENTER];
	message_.color = UtilityCommon::WHITE;

	amount_.fontHandle = fontMng_.CreateMyFont(resMng_.GetFontName("fontDot"), 32, 5);
	amount_.string = L"%dG";
	amount_.color = UtilityCommon::WHITE;

	int checkFont = fontMng_.CreateMyFont(resMng_.GetFontName("fontDot"), 32, 5);
	yes_.fontHandle = checkFont;
	yes_.pos = { Application::SCREEN_HALF_X - 100, 680 };
	yes_.string = L"YES";
	yes_.color = UtilityCommon::WHITE;

	no_.fontHandle = checkFont;
	no_.pos = { Application::SCREEN_HALF_X + 100, 680 };
	no_.string = L"NO";
	no_.color = UtilityCommon::WHITE;

	// アニメーション
	textAnimation_ = std::make_unique<ComponentTextAnimation>(message_, 0.05f);
	textAnimation_->Init();

	// UIの追加
	myMoney_ = std::make_unique<UiMoney>();
	myMoney_->Init();
	myMoney_->SetPos(Vector2{ 950, 48 });
}

void SceneShop::NormalUpdate()
{
	for (const auto& backGround : backGround_)
	{
		backGround->Update();
	}

	textAnimation_->Update();
	frameCount_ += scnMng_.GetDeltaTime();
	myMoney_->Update();
	stateUpdate_();
}

void SceneShop::NormalDraw()
{
	// 背景描画
	for (const auto& backGround : backGround_)
	{
		backGround->Draw();
	}

	// 毎フレーム変動しない共通の計算をループ外へ追い出す
	const float SPACING_X = static_cast<float>(Application::SCREEN_SIZE_X) / static_cast<float>(COL + 1);
	const float SPACING_Y = static_cast<float>(Application::SCREEN_SIZE_Y) / static_cast<float>(ROW + 1);
	const Vector2 ITEM_SIZE = { 128, 128 };
	const float HALF_ITEM_Y_PLUS_10 = (ITEM_SIZE.y / 2.0f) + 10.0f;

	// サイン波のベース値（i を足す前の共通値）を事前に計算
	const float BASE_WAVE_ANGLE = static_cast<float>(frameCount_) * 5.0f;

	// 購入品の描画
	for (int i = 0; i < ITEM_MAX; i++)
	{
		const Exhibits& exhibits = exhibits_[i];
		auto& material = exhibitsMaterial_[i];
		auto& renderer = exhibitsRenderer_[i];

		// テキストカラー
		int color = UtilityCommon::WHITE;

		// 配置座標の計算
		int column = i % COL;
		int row = i / COL;

		Vector2 basePos;
		basePos.x = SPACING_X * static_cast<float>(column + 1);
		basePos.y = SPACING_Y * static_cast<float>(row + 1);

		// 選択状態によるスケール変更
		float scale = 1.0f;
		if (selectIndex_ == i)
		{
			scale = 1.2f;
			color = UtilityCommon::RED;
		}

		// アイテム位置を上下に揺らす
		Vector2 itemPos = basePos;
		itemPos.y += sinf(BASE_WAVE_ANGLE + static_cast<float>(i)) * 5.0f;

		// 定数バッファの更新
		material->SetConstBuf(0, FLOAT4{ 1.0f, 1.0f, 1.0f, 1.0f });
		material->SetConstBuf(1, FLOAT4{ static_cast<float>(exhibits.division.x), static_cast<float>(exhibits.division.y),static_cast<float>(exhibits.drawIndex), 0.0f });
		renderer->MakeSquereVertex(itemPos, ITEM_SIZE, 0.0f, scale);

		// アイテム描画
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(UtilityCommon::ALPHA_MAX));
		renderer->Draw();
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		// 金額の表示
		Vector2 amountPos = basePos;
		amountPos.y += HALF_ITEM_Y_PLUS_10;
		amount_.pos = amountPos;
		amount_.data1 = exhibits.amount;
		amount_.color = color;
		amount_.DrawFormatCenter();

		// 矢印の描画 (選択中のみ)
		if (selectIndex_ == i)
		{
			arrowPos_ = Vector2::AddVector2(amountPos, ARROW_LOCAL_POS);
		}
	}

	// テキストメッセージの描画
	textAnimation_->Draw();

	// UIの描画
	myMoney_->Draw();

	// 状態が確認時のみ
	if (state_ == STATE::CHECK)
	{
		DrawCheck();
	}

	// 矢印の描画
	DrawRotaGraph(
		arrowPos_.x,
		arrowPos_.y,
		1.0f,
		0.0f,
		arrowHandle_,
		true
	);
}

void SceneShop::UpdateSelect()
{
	if (inputMng_.IsTrgDown(InputManager::TYPE::SELECT_CANCEL, padNo_))
	{
		//シーンを戻す
		scnMng_.PopScene();
		return;
	}
	else if (inputMng_.IsTrgDown(InputManager::TYPE::SELECT_DOWN, padNo_))
	{
		selectIndex_ = UtilityCommon::WrapStepIndex(selectIndex_, COL, 0, ITEM_MAX);
		return;
	}
	else if (inputMng_.IsTrgDown(InputManager::TYPE::SELECT_UP, padNo_))
	{
		selectIndex_ = UtilityCommon::WrapStepIndex(selectIndex_, -COL, 0, ITEM_MAX);
		return;
	}
	else if (inputMng_.IsTrgDown(InputManager::TYPE::SELECT_LEFT, padNo_))
	{
		selectIndex_ = UtilityCommon::WrapStepIndex(selectIndex_, -1, 0, ITEM_MAX);
		return;
	}
	else if (inputMng_.IsTrgDown(InputManager::TYPE::SELECT_RIGHT, padNo_))
	{
		selectIndex_ = UtilityCommon::WrapStepIndex(selectIndex_, 1, 0, ITEM_MAX);
		return;
	}
	else if (inputMng_.IsTrgDown(InputManager::TYPE::SELECT_DECISION, padNo_))
	{
		if (scoreManager_.GetTotalScore() >= exhibits_[selectIndex_].amount)
		{
			ChangeState(STATE::CHECK);
			return;
		}
		else
		{
			message_.string = TEXT_MAP.at(TEXT_TYPE::INSUFFICIENT_FUNDS);
			textAnimation_->SetCharacterString(message_);
			return;
		}
	}
}

void SceneShop::UpdateCheck()
{
	if (inputMng_.IsTrgDown(InputManager::TYPE::SELECT_CANCEL, padNo_))
	{
		PurchaseCancel();
		return;
	}
	else if (inputMng_.IsTrgDown(InputManager::TYPE::SELECT_LEFT, padNo_))
	{
		isPurchase_ = true;
		return;
	}
	else if (inputMng_.IsTrgDown(InputManager::TYPE::SELECT_RIGHT, padNo_))
	{
		isPurchase_ = false;
		return;
	}
	else if (inputMng_.IsTrgDown(InputManager::TYPE::SELECT_DECISION, padNo_))
	{
		isPurchase_ ? Purchase() : PurchaseCancel();
		return;
	}
}

void SceneShop::PurchaseCancel()
{
	// 状態を戻す
	ChangeState(STATE::SELECT);

	message_.string = TEXT_MAP.at(TEXT_TYPE::ENTER);
	textAnimation_->SetCharacterString(message_);
}

void SceneShop::ChangeState(const STATE state)
{
	state_ = state;
	changeStateMap_[state_]();
}

void SceneShop::ChangeStateSelect()
{
	stateUpdate_ = std::bind(&SceneShop::UpdateSelect, this);
}

void SceneShop::ChangeStateCheck()
{
	message_.string = TEXT_MAP.at(TEXT_TYPE::CONFIRMATION);
	textAnimation_->SetCharacterString(message_);
	stateUpdate_ = std::bind(&SceneShop::UpdateCheck, this);
	isPurchase_ = true;
}

void SceneShop::Purchase()
{
	// アイテムを追加する
	const Exhibits& exhibits = exhibits_[selectIndex_];
	const Vector2F createPos = gimmickMng_.GetShopPos();

	// ランダムに散らすためのオフセット計算
	float offsetX = static_cast<float>(GetRand(250) - GetRand(250));
	float offsetY = static_cast<float>(-(GetRand(50) + 10)); // 必ずマイナス値（ショップより上）にする

	Vector2F randomizedPos;
	randomizedPos.x = createPos.x + offsetX;
	randomizedPos.y = createPos.y + offsetY;

	// 生成
	switch (exhibits.type)
	{
	case ItemTypes::TYPE::FOOD:
		itemMng_.CreateFoodItem(static_cast<ItemTypes::FOOD_TYPE>(exhibits.drawIndex), randomizedPos);
		break;

	case ItemTypes::TYPE::AVILITY:
		itemMng_.CreateAvilityItem(static_cast<AvilityTypes::TYPE>(exhibits.drawIndex), randomizedPos);
		break;

	case ItemTypes::TYPE::POTION:
		itemMng_.CreatePotionItem(static_cast<ItemTypes::POTION_TYPE>(exhibits.drawIndex), randomizedPos);
		break;

	default:
		break;
	}
	
	// 金額を減らす
	scoreManager_.AddTotalScore(-exhibits.amount);

	// 状態遷移
	ChangeState(STATE::SELECT);

	// テキスト処理
	message_.string = TEXT_MAP.at(TEXT_TYPE::THANK_YOU);
	textAnimation_->SetCharacterString(message_);
}

void SceneShop::DrawCheck()
{
	Vector2 basePos = {};
	if (isPurchase_)
	{
		yes_.color = UtilityCommon::RED;
		arrowPos_ = Vector2::AddVector2(yes_.pos, ARROW_LOCAL_POS);
		no_.color = UtilityCommon::WHITE;
	}
	else
	{
		no_.color = UtilityCommon::RED;
		arrowPos_ = Vector2::AddVector2(no_.pos, ARROW_LOCAL_POS);
		yes_.color = UtilityCommon::WHITE;
	}

	yes_.DrawCenter();
	no_.DrawCenter();
}