#include "../../Object/Item/ItemBase.h"
#include "../../Object/Item/ItemAvility.h"
#include "../../Object/Item/ItemCoin.h"
#include "../../Object/Item/ItemCoinBag.h"
#include "../../Object/Item/ItemFood.h"
#include "../../Object/Item/ItemTreasure.h"
#include "../../System/ItemGenerator.h"
#include "ItemManager.h"

void ItemManager::Init()
{
	if (itemList_.empty()) return;

	for (auto& item : itemList_)
	{
		item->Init();
	}
}

void ItemManager::Update()
{
	if (itemList_.empty()) return;

	for (auto& item : itemList_)
	{
		item->Update();
	}
}

void ItemManager::Draw()
{
	if (itemList_.empty()) return;

	for (auto& item : itemList_)
	{
		item->Draw();
	}
}

void ItemManager::Add(std::unique_ptr<ItemBase> item)
{
	// 空の場合
	if (!item)
	{
		// 終了
		return;
	}

	// 初期化処理を実行
	item->Init();

	// アイテムを追加
	itemList_.push_back(std::move(item));
}

void ItemManager::CreateAvilityItem(const AvilityTypes::TYPE type)
{
	// 生成
	auto item = itemGenerator_->CreateAvility(type);

	// 初期化
	item->Init();

	// 格納
	itemList_.push_back(std::move(item));
}

void ItemManager::CreateFoodItem(const ItemTypes::FOOD_TYPE type)
{
	// 生成
	auto item = itemGenerator_->CreateFood(type);

	// 初期化
	item->Init();

	// 格納
	itemList_.push_back(std::move(item));
}

void ItemManager::CreateTreasureItem(const ItemTypes::TREASURE_TYPE type)
{
	// 生成
	auto item = itemGenerator_->CreateTreasure(type);

	// 初期化
	item->Init();

	// 格納
	itemList_.push_back(std::move(item));
}

void ItemManager::CreateMoneyItem(const int moneyAmount)
{
	int bagCount = moneyAmount / 1000;
	int coinCount = (moneyAmount % 1000) / 1000;
	coinCount = (moneyAmount % 1000) / 100;

	// コインバッグの生成とリストへの追加
	for (int i = 0; i < bagCount; i++)
	{
		auto item = itemGenerator_->CreateCoinBag();
		item->Init();
		itemList_.push_back(std::move(item));
	}

	// コインの生成とリストへの追加
	for (int i = 0; i < coinCount; i++)
	{
		auto item = itemGenerator_->CreateCoin();
		item->Init();
		itemList_.push_back(std::move(item));
	}
}

void ItemManager::DebugDraw()
{
	for (auto& item : itemList_)
	{
		item->DebugDraw();
	}
}

void ItemManager::Sweep()
{
	// 終了したアイテムを並び変える
	auto it = std::remove_if(itemList_.begin(), itemList_.end(),
		[](const std::unique_ptr<ItemBase>& item)
		{
			return item->IsDelete();
		});

	// 終了したコライダを削除する
	itemList_.erase(it, itemList_.end());
}

void ItemManager::Clear()
{
	if (itemList_.empty()) return;

	for (auto& item : itemList_)
	{
		item->Delete();
	}
	itemList_.clear();
}

ItemManager::ItemManager()
{
	// アイテム生成処理の生成
	itemGenerator_ = std::make_unique<ItemGenerator>();
	itemGenerator_->InitParameter();
}

ItemManager::~ItemManager()
{
}