#include "../../Object/Item/ItemBase.h"
#include "../../Object/Item/ItemAvility.h"
#include "../../Object/Item/ItemMoney.h"
#include "../../Object/Item/ItemFood.h"
#include "../../Object/Item/ItemTreasure.h"
#include "../../Object/Item/ItemPotion.h"
#include "../../System/ItemGenerator.h"
#include "../../Utility/UtilityCommon.h"
#include "../Manager/Common/Camera.h"
#include "../Manager/Common/SceneManager.h"
#include "ItemManager.h"

void ItemManager::Init()
{
	if (itemMap_.empty()) return;

	for (auto& itemList : itemMap_)
	{
		for (auto& item : itemList.second)
		{
			item->Init();
		}
	}
}

void ItemManager::Update()
{
	if (itemMap_.empty()) return;

	for (auto& itemList : itemMap_)
	{
		for (auto& item : itemList.second)
		{
			// カメラ範囲内の場合
			auto& parameter = item->GetParameter();
			bool isInScreen = mainCamera.IsInScreenCircle(parameter.pos_, parameter.hitRadius_);
			if (isInScreen)
			{
				item->Update();
			}
			item->SetIsActive(isInScreen);
		}
	}
}

void ItemManager::Draw()
{
	if (itemMap_.empty()) return;

	for (auto& itemList : itemMap_)
	{
		for (auto& item : itemList.second)
		{
			item->Draw();
		}
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
	itemMap_[item->GetParameter().itemType_].push_back(std::move(item));
}

void ItemManager::CreateAvilityItem(const AvilityTypes::TYPE type, const Vector2F& pos)
{
	// 生成
	auto item = itemGenerator_->CreateAvility(type);

	// 座標設定
	item->GetParameter().pos_ = pos;

	// 初期化
	item->Init();

	// 格納
	itemMap_[ItemTypes::TYPE::ABILITY].push_back(std::move(item));
}

void ItemManager::CreateFoodItem(const ItemTypes::FOOD_TYPE type, const Vector2F& pos, const ParameterActor::DIR fallDir)
{	
	// 生成
	auto item = itemGenerator_->CreateFood(type);

	// 座標設定
	item->GetParameter().pos_ = pos;

	// 落下方向設定
	item->GetParameter().gravityDir_ = fallDir;

	// 初期化
	item->Init();

	// 格納
	itemMap_[ItemTypes::TYPE::FOOD].push_back(std::move(item));
}

void ItemManager::CreateTreasureItem(const ItemTypes::TREASURE_TYPE type, const Vector2F& pos)
{
	// 生成
	auto item = itemGenerator_->CreateTreasure(type);

	// 座標設定
	item->GetParameter().pos_ = pos;

	// 初期化
	item->Init();

	// 格納
	itemMap_[ItemTypes::TYPE::TREASURE].push_back(std::move(item));
}

void ItemManager::CreatePotionItem(const ItemTypes::POTION_TYPE type, const Vector2F& pos)
{
	// 生成
	auto item = itemGenerator_->CreatePotion(type);

	// 座標設定
	item->GetParameter().pos_ = pos;

	// 初期化
	item->Init();

	// 格納
	itemMap_[ItemTypes::TYPE::POTION].push_back(std::move(item));
}

void ItemManager::CreateMoneyItem(const int moneyAmount, const Vector2F& pos)
{
	auto items = itemGenerator_->CreateMonies(moneyAmount, pos);
	for (auto& item : items)
	{
		item->Init();
		itemMap_[ItemTypes::TYPE::MONEY].push_back(std::move(item));
	}
}

void ItemManager::CreateTreasureChestItems(const Vector2F& tresureChestPos)
{
	auto items = itemGenerator_->CreateTreasureChestItemList(tresureChestPos);
	for (auto& item : items)
	{
		item->Init();
		auto type = item->GetParameter().itemType_;
		itemMap_[type].push_back(std::move(item));
	}
}

void ItemManager::CreateItemList(const std::vector<Vector2F>& itemList)
{
	// 各アイテムのドロップ重み（数値を変更するだけで確率を簡単に調整できます）
	const int WEIGHT_FOOD = 5;
	const int WEIGHT_AVILITY = 3;
	const int WEIGHT_TREASURE = 2;
	const int WEIGHT_POTION = 4;
	const int WEIGHT_NONE = 2; // アイテムなしの確率

	// 重みの合計値を計算
	const int TOTAL_WEIGHT = WEIGHT_FOOD + WEIGHT_AVILITY + WEIGHT_TREASURE + WEIGHT_POTION + WEIGHT_NONE;

	for (const Vector2F& pos : itemList)
	{
		// 範囲でランダム値を獲得
		int randValue = GetRand(TOTAL_WEIGHT - 1);

		// 累積確率による判定
		if (randValue < WEIGHT_FOOD)
		{
			CreateFoodItem(static_cast<ItemTypes::FOOD_TYPE>(GetRand(ItemTypes::FOOD_TYPE_MAX - 1)), pos);
		}
		else if ((randValue -= WEIGHT_FOOD) < WEIGHT_AVILITY)
		{
			CreateAvilityItem(static_cast<AvilityTypes::TYPE>(GetRand(AvilityTypes::AVILITY_TYPE_MAX - 1)), pos);
		}
		else if ((randValue -= WEIGHT_AVILITY) < WEIGHT_TREASURE)
		{
			CreateTreasureItem(static_cast<ItemTypes::TREASURE_TYPE>(GetRand(ItemTypes::TREASURE_TYPE_MAX - 1)), pos);
		}
		else if ((randValue -= WEIGHT_TREASURE) < WEIGHT_POTION)
		{
			CreatePotionItem(static_cast<ItemTypes::POTION_TYPE>(GetRand(ItemTypes::POTION_TYPE_MAX - 1)), pos);
		}
	}
}

void ItemManager::DebugDraw()
{
	for (auto& itemList : itemMap_)
	{
		for (auto& item : itemList.second)
		{
			item->DebugDraw();
		}
	}
}

const int ItemManager::GetItemCount(const ItemTypes::TYPE type) const
{
	if (itemMap_.find(type) == itemMap_.end())
	{
		return 0;
	}

	return static_cast<int>(itemMap_.at(type).size());
}

void ItemManager::Sweep()
{
	for (auto& itemList : itemMap_)
	{
		auto it = std::remove_if(itemList.second.begin(), itemList.second.end(),
			[](const std::unique_ptr<ItemBase>& enemy)
			{
				if (enemy == nullptr)
				{
					return true;
				}
				return enemy->IsDelete();
			});
		itemList.second.erase(it, itemList.second.end());
	}
}

void ItemManager::CarryAndClear()
{
	if (itemMap_.empty())
	{
		return;
	}

	// 一時退避用のコンテナ
	std::unordered_map<ItemTypes::TYPE, std::vector<std::unique_ptr<ItemBase>>> keepMap;

	// 持ち越しと削除 
	for (auto& itemList : itemMap_)
	{
		for (auto& item : itemList.second)
		{
			// 持ち越しの場合
			if (item->IsCarryOver())
			{
				// 一時退避
				keepMap[item->GetParameter().itemType_].push_back(std::move(item));
			}
			else
			{
				// 削除
				item->Delete();
			}
		}
	}

	// 中身を削除
	itemMap_.clear();

	// 退避してたアイテムを戻す
	itemMap_ = std::move(keepMap);
}

void ItemManager::SetAllIsCarry(const bool isCarry)
{
	if (itemMap_.empty()) return;

	for (auto& itemList : itemMap_)
	{
		for (auto& item : itemList.second)
		{
			item->SetIsCarryOver(isCarry);
		}
	}
}

void ItemManager::Clear()
{
	if (itemMap_.empty()) return;

	for (auto& itemList : itemMap_)
	{
		for (auto& item : itemList.second)
		{
			// 削除
			item->Delete();
		}
	}

	// 中身を削除
	itemMap_.clear();
}

ItemBase* ItemManager::GetNearestFood(const Vector2F& basePos)
{
	auto& foodList = itemMap_[ItemTypes::TYPE::FOOD];
	if (foodList.empty())
	{
		return nullptr;
	}

	ItemBase* nearestFood = nullptr;
	float minDistanceSq = FLT_MAX;

	for (const auto& item : foodList)
	{
		Vector2F diff = Vector2F::SubVector2F(item->GetParameter().pos_, basePos);
		float distSq = diff.x * diff.x + diff.y * diff.y;

		if (distSq < minDistanceSq)
		{
			minDistanceSq = distSq;
			nearestFood = item.get(); 
		}
	}

	return nearestFood;
}

std::vector<SceneShop::Exhibits> ItemManager::GetRandomExhibits(const int abilityNum, const int potionNum, const int foodNum)
{
	std::vector<SceneShop::Exhibits> exhibitsList;

	for (int i = 0; i < abilityNum; i++)
	{
		SceneShop::Exhibits exhibits = {};
		const auto& item = itemGenerator_->CreateAvility(static_cast<AvilityTypes::TYPE>(UtilityCommon::GetRandomCount(AvilityTypes::AVILITY_TYPE_MAX - 1, 0)));
		item->Init();
		const auto& parameter = item->GetParameter();
		exhibits.handle = parameter.texture_;
		exhibits.drawIndex = parameter.spriteIndex_;
		exhibits.amount = parameter.amount_;
		exhibits.division = parameter.divisionNum_;
		exhibits.message = parameter.shopMessage_;
		exhibits.type = ItemTypes::TYPE::ABILITY;
		exhibitsList.push_back(exhibits);
		item->Delete();
	}
	for (int i = 0; i < potionNum; i++)
	{
		SceneShop::Exhibits exhibits = {};
		const auto& item = itemGenerator_->CreatePotion(static_cast<ItemTypes::POTION_TYPE>(UtilityCommon::GetRandomCount(ItemTypes::POTION_TYPE_MAX - 1, 0)));
		item->Init();
		const auto& parameter = item->GetParameter();
		exhibits.handle = parameter.texture_;
		exhibits.drawIndex = parameter.spriteIndex_;
		exhibits.amount = parameter.amount_;
		exhibits.division = parameter.divisionNum_;
		exhibits.message = parameter.shopMessage_;
		exhibits.type = ItemTypes::TYPE::POTION;
		exhibitsList.push_back(exhibits);
		item->Delete();
	}
	for (int i = 0; i < foodNum; i++)
	{
		SceneShop::Exhibits exhibits = {};
		const auto& item = itemGenerator_->CreateFood(static_cast<ItemTypes::FOOD_TYPE>(UtilityCommon::GetRandomCount(ItemTypes::FOOD_TYPE_MAX - 1, 0)));
		item->Init();
		const auto& parameter = item->GetParameter();
		exhibits.handle = parameter.texture_;
		exhibits.drawIndex = parameter.spriteIndex_;
		exhibits.amount = parameter.amount_;
		exhibits.division = parameter.divisionNum_;
		exhibits.message = parameter.shopMessage_;
		exhibits.type = ItemTypes::TYPE::FOOD;
		exhibitsList.push_back(exhibits);
		item->Delete();
	}

	return exhibitsList;
}

void ItemManager::CreateAbilityTrial(const std::vector<Vector2F>& itemList)
{
	if (itemList.size() < static_cast<size_t>(AvilityTypes::AVILITY_TYPE_MAX))
	{
		return;
	}

	for (int i = 0; i < AvilityTypes::AVILITY_TYPE_MAX; i++)
	{
		// 種類取得
		AvilityTypes::TYPE type = static_cast<AvilityTypes::TYPE>(i);

		// アイテムの生成
		CreateAvilityItem(type, itemList[i]);

		// 座標の登録
		abilityTrialPositionMap_[type] = itemList[i];
	}
}

void ItemManager::CheckAbilityTrial()
{
	// 各アビリティが存在するかどうかを管理する配列
	std::vector<bool> hasAbilityArray(AvilityTypes::AVILITY_TYPE_MAX, false);

	// 存在するアビリティアイテムをチェック
	auto& abilityItemList = itemMap_[ItemTypes::TYPE::ABILITY];
	for (const auto& item : abilityItemList)
	{
		if (item == nullptr)
		{
			continue;
		}

		// 生ポインタを取得してキャスト
		ItemAvility* itemAbility = dynamic_cast<ItemAvility*>(item.get());
		if (itemAbility != nullptr)
		{
			auto type = itemAbility->GetParameter().type_;
			int index = static_cast<int>(type);
			if (index >= 0 && index < AvilityTypes::AVILITY_TYPE_MAX)
			{
				hasAbilityArray[index] = true;
			}
		}
	}

	// 存在しないアビリティアイテムを再生成
	for (int i = 0; i < AvilityTypes::AVILITY_TYPE_MAX; i++)
	{
		if (!hasAbilityArray[i])
		{
			AvilityTypes::TYPE type = static_cast<AvilityTypes::TYPE>(i);

			// 登録された座標が存在する場合のみ生成
			auto it = abilityTrialPositionMap_.find(type);
			if (it != abilityTrialPositionMap_.end())
			{
				CreateAvilityItem(type, it->second);
			}
		}
	}
}

void ItemManager::CheckTutorialAbilityItem(const AvilityTypes::TYPE type, const Vector2F& pos)
{
	if (itemMap_[ItemTypes::TYPE::ABILITY].empty())
	{
		CreateAvilityItem(type, pos);
	}
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