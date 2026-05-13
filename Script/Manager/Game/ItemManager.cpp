#include "../../Object/Item/ItemBase.h"
#include "../../Object/Item/ItemAvility.h"
#include "ItemManager.h"

ItemManager::ItemManager()
{
}

ItemManager::~ItemManager()
{
}

void ItemManager::Init()
{
	for (auto& item : itemList_)
	{
		item->Init();
	}
}

void ItemManager::Update()
{
	for (auto& item : itemList_)
	{
		item->Update();
	}
}

void ItemManager::Draw()
{
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
	// アイテムを追加
	itemList_.push_back(std::move(item));
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