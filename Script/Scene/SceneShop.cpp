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
#include "../Manager/Game/UiManager.h"
#include "../Factory/FactoryComponent.h"
#include "../Utility/UtilityCommon.h"
#include "../Render/PixelMaterial.h"
#include "../Render/PixelRenderer.h"
#include "../Object/Stage/BackGround.h"
#include "../Component/ComponentTextAnimation.h"
#include "SceneShop.h"

SceneShop::SceneShop(const Input::JOYPAD_NO padNo) :
	padNo_(padNo)
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
}

void SceneShop::NormalUpdate()
{
	for (const auto& backGround : backGround_)
	{
		backGround->Update();
	}

	stateUpdate_();
}

void SceneShop::NormalDraw()
{
	// 背景描画
	for (const auto& backGround : backGround_)
	{
		backGround->Draw();
	}

	// 購入品の描画
	for (int i = 0; i < ITEM_MAX; i++)
	{
		const Exhibits& exhibits = exhibits_[i];
		auto& material = exhibitsMaterial_[i];
		auto& renderer = exhibitsRenderer_[i];

		// アイテムのサイズ
		Vector2 size = { 128, 128 };

		// グリッド全体のサイズを計算
		float totalWidth = size.x * (COL + 1);
		float totalHeight = size.y * (ROW + 1);

		// 画面内の余白を均等に分配するための隙間（間隔）を計算
		float spacingX = static_cast<float>(Application::SCREEN_SIZE_X) / static_cast<float>(COL + 1);
		float spacingY = static_cast<float>(Application::SCREEN_SIZE_Y) / static_cast<float>(ROW + 1);

		// インデックスから行列の位置を計算
		int column = i % COL;
		int row = i / COL;

		// 均等配置の座標計算
		Vector2 pos;
		pos.x = spacingX * (column + 1);
		pos.y = spacingY * (row + 1);

		// 定数バッファの更新
		material->SetConstBuf(0, FLOAT4{ 1.0f, 1.0f, 1.0f, 1.0f });
		material->SetConstBuf(1, FLOAT4{ (float)exhibits.division.x, (float)exhibits.division.y, (float)exhibits.drawIndex, 0.0f });
		
		// メッシュ生成
		renderer->MakeSquereVertex(pos, size);
		
		// 描画処理
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)UtilityCommon::ALPHA_MAX);
		renderer->Draw();
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		// 矢印を描画
		if (selectIndex_ == i)
		{
			// 座標を調整
			pos = Vector2::AddVector2(pos, Vector2(64, 64));

			DrawRotaGraph(
				pos.x,
				pos.y,
				1.0f,
				0.0f,
				arrowHandle_,
				true
			);
		}
	}
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
			return;
		}
	}
}

void SceneShop::UpdateCheck()
{
	if (inputMng_.IsTrgDown(InputManager::TYPE::SELECT_CANCEL, padNo_))
	{
		// 状態を戻す
		ChangeState(STATE::SELECT);
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
		Purchase(); 
		ChangeState(STATE::SELECT);
		return;
	}
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
	stateUpdate_ = std::bind(&SceneShop::UpdateCheck, this);
	isPurchase_ = true;
}

void SceneShop::Purchase()
{
	// アイテムを追加する
	const Exhibits& exhibits = exhibits_[selectIndex_];
	const Vector2F createPos = gimmickMng_.GetShopPos();

	// 生成
	switch (exhibits.type)
	{
	case ItemTypes::TYPE::FOOD:
		itemMng_.CreateFoodItem(static_cast<ItemTypes::FOOD_TYPE>(exhibits.drawIndex), createPos);
		break;

	case ItemTypes::TYPE::AVILITY:
		itemMng_.CreateAvilityItem(static_cast<AvilityTypes::TYPE>(exhibits.drawIndex), createPos);
		break;

	case ItemTypes::TYPE::POTION:
		itemMng_.CreatePotionItem(static_cast<ItemTypes::POTION_TYPE>(exhibits.drawIndex), createPos);
		break;

	default:
		break;
	}	
	
	// 金額を減らす
	scoreManager_.AddTotalScore(-exhibits.amount);
}