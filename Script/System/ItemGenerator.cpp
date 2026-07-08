#include <DxLib.h>
#include "../Utility/UtilityLoad.h"
#include "../Object/Item/ItemAvility.h"
#include "../Object/Item/ItemMoney.h"
#include "../Object/Item/ItemFood.h"
#include "../Object/Item/ItemTreasure.h"
#include "../Object/Item/ItemPotion.h"
#include "../Manager/Game/PlayerManager.h"
#include "ItemGenerator.h"

ItemGenerator::ItemGenerator() :
	playerManager_(PlayerManager::GetInstance())
{
}

ItemGenerator::~ItemGenerator()
{
}

std::unique_ptr<ItemAvility> ItemGenerator::CreateAvility(const AvilityTypes::TYPE type)
{
	std::unique_ptr<ParameterItemAvility> parameter = std::make_unique<ParameterItemAvility>(*templateAvilityParameterMap_.at(type));
	std::unique_ptr<ItemAvility> item = std::make_unique<ItemAvility>(std::move(parameter));
    return item;
}

std::unique_ptr<ItemFood> ItemGenerator::CreateFood(const ItemTypes::FOOD_TYPE type)
{
	std::unique_ptr<ParameterItemFood> parameter = std::make_unique<ParameterItemFood>(*templateFoodParameterMap_.at(type));
	std::unique_ptr<ItemFood> item = std::make_unique<ItemFood>(std::move(parameter));
	return item;
}

std::unique_ptr<ItemTreasure> ItemGenerator::CreateTreasure(const ItemTypes::TREASURE_TYPE type)
{
	std::unique_ptr<ParameterItemTreasure> parameter = std::make_unique<ParameterItemTreasure>(*templateTreasureParameterMap_.at(type));
	std::unique_ptr<ItemTreasure> item = std::make_unique<ItemTreasure>(std::move(parameter));
	return item;
}

std::vector<std::unique_ptr<ItemMoney>> ItemGenerator::CreateMonies(const int moneyAmount, const Vector2F& pos)
{
	std::vector<std::unique_ptr<ItemMoney>> moneyList;
	int bagCount = moneyAmount / 1000;
	int coinCount = (moneyAmount % 1000) / 1000;
	coinCount = (moneyAmount % 1000) / 100;

	// コインバッグの生成とリストへの追加
	for (int i = 0; i < bagCount; i++)
	{
		std::unique_ptr<ParameterItemMoney> parameter = std::make_unique<ParameterItemMoney>(*templateMoneyParameterMap_.at(ItemTypes::MONEY_TYPE::COIN_BAG));
		std::unique_ptr<ItemMoney> item = std::make_unique<ItemMoney>(std::move(parameter));
		moneyList.push_back(std::move(item));
	}

	// コインの生成とリストへの追加
	for (int i = 0; i < coinCount; i++)
	{
		std::unique_ptr<ParameterItemMoney> parameter = std::make_unique<ParameterItemMoney>(*templateMoneyParameterMap_.at(ItemTypes::MONEY_TYPE::COIN));
		std::unique_ptr<ItemMoney> item = std::make_unique<ItemMoney>(std::move(parameter));
		moneyList.push_back(std::move(item));
	}

	// 座標やノックバック量の設定
	for (auto& item : moneyList)
	{
		// 座標定義
		item->GetParameter().pos_ = Vector2F::SubVector2F(Vector2F::AddVector2F(pos, Vector2(GetRand(RANGE.x), GetRand(RANGE.y)).ToVector2F()), OFFSET);

		// ノックバックパワーを設定
		item->GetParameter().knockBackPower_ = {
			GetRand(KNOCK_BACK_POWER_MAX.x - KNOCK_BACK_POWER_MIN.x) + KNOCK_BACK_POWER_MAX.x,
			-(GetRand(KNOCK_BACK_POWER_MAX.y - KNOCK_BACK_POWER_MIN.y) + KNOCK_BACK_POWER_MAX.y)
		};

		// 1/2でノックバック方向を変える
		item->GetParameter().knockBackPower_.x *= GetRand(1) == 0 ? -1.0f : 1.0f;
	}

	return moneyList;
}

std::unique_ptr<ItemPotion> ItemGenerator::CreatePotion(const ItemTypes::POTION_TYPE type)
{
	std::unique_ptr<ParameterItemPotion> parameter = std::make_unique<ParameterItemPotion>(*templatePotionParameterMap_.at(type));
	std::unique_ptr<ItemPotion> item = std::make_unique<ItemPotion>(std::move(parameter));
	return item;
}

std::vector<std::unique_ptr<ItemBase>> ItemGenerator::CreateTreasureChestItemList(const Vector2F& terasureChestPos)
{
	std::vector<std::unique_ptr<ItemBase>> itemList;
	constexpr int ADD_CREATE_AVILITY_NUM = 2;
	constexpr int CREATE_FOOD_NUM_MIN = 2;
	constexpr int CREATE_FOOD_NUM_MAX = 5;

	// アビリティアイテムの生成する数を決定
	int createCountAvility = playerManager_.GetPlayerNum() + GetRand(ADD_CREATE_AVILITY_NUM);

	// 食べ物の生成する数を決定
	int createCountFood = CREATE_FOOD_NUM_MIN + GetRand(CREATE_FOOD_NUM_MAX - CREATE_FOOD_NUM_MIN);

	// お金をいくら生成するかの番号を決定
	int createMoniesIndex = GetRand(static_cast<int>(CREATE_MONEIES.size()) - 1);

	// 一定の確率で宝物を生成
	int createCountTreasure = 0 == GetRand(2) ? 1 : 0;

	// 一定の確率で強化アイテムを生成
	int createPowerUpItem = 0 == GetRand(1) ? 1 : 0;

	// 各種生成
	for (int i = 0; i < createCountAvility; i++) 
	{
		// 種類の決定
		AvilityTypes::TYPE type = static_cast<AvilityTypes::TYPE>(GetRand(AvilityTypes::AVILITY_TYPE_MAX - 1));
		auto item = CreateAvility(type);
		itemList.push_back(std::move(item));
	}
	for (int i = 0; i < createCountFood; i++)
	{
		// 種類の決定
		ItemTypes::FOOD_TYPE type = static_cast<ItemTypes::FOOD_TYPE>(GetRand(ItemTypes::FOOD_TYPE_MAX - 1));
		auto item = CreateFood(type);
		itemList.push_back(std::move(item));
	}
	for (int i = 0; i < createCountTreasure; i++)
	{
		// 種類の決定
		ItemTypes::TREASURE_TYPE type = static_cast<ItemTypes::TREASURE_TYPE>(GetRand(ItemTypes::TREASURE_TYPE_MAX - 1));
		auto item = CreateTreasure(type);
		itemList.push_back(std::move(item));
	}
	for (int i = 0; i < createPowerUpItem; i++)
	{
		// 種類の決定
		ItemTypes::POTION_TYPE type = static_cast<ItemTypes::POTION_TYPE>(GetRand(ItemTypes::POTION_TYPE_MAX - 1));
		auto item = CreatePotion(type);
		itemList.push_back(std::move(item));
	}

	// お金の生成
	auto moneyList = CreateMonies(CREATE_MONEIES[createMoniesIndex], terasureChestPos);
	for (auto& money : moneyList)
	{
		itemList.push_back(std::move(money));
	}

	// 座標やノックバック量の設定
	for (auto& item : itemList)
	{
		// 座標定義
		item->GetParameter().pos_ = Vector2F::SubVector2F(Vector2F::AddVector2F(terasureChestPos, Vector2(GetRand(RANGE.x), GetRand(RANGE.y)).ToVector2F()), OFFSET);
	
		// ノックバックパワーを設定
		item->GetParameter().knockBackPower_ = {
			GetRand(KNOCK_BACK_POWER_MAX.x - KNOCK_BACK_POWER_MIN.x) + KNOCK_BACK_POWER_MAX.x,
			-(GetRand(KNOCK_BACK_POWER_MAX.y - KNOCK_BACK_POWER_MIN.y) + KNOCK_BACK_POWER_MAX.y)
		};

		// 1/2でノックバック方向を変える
		item->GetParameter().knockBackPower_.x *= GetRand(1) == 0 ? -1.0f : 1.0f;
	}

	return itemList;
}

void ItemGenerator::InitParameter()
{
	// 情報の取得
	const auto jsonParameterMap = UtilityLoad::GetJsonMapArrayData("ItemsParameter");

	// アビリティ情報生成
	for (int i = 0; i < AvilityTypes::AVILITY_TYPE_MAX; i++)
	{
		AvilityTypes::TYPE type = static_cast<AvilityTypes::TYPE>(i);
		std::string name = AvilityTypes::AVILITY_NAME_MAP.at(type);
		auto parameterAvility = std::make_unique<ParameterItemAvility>();
		parameterAvility->LoadParameter(jsonParameterMap, name);
		parameterAvility->type_ = type;
		templateAvilityParameterMap_.emplace(type, std::move(parameterAvility));
	}

	// 食べ物情報生成
	for (int i = 0; i < ItemTypes::FOOD_TYPE_MAX; i++)
	{
		ItemTypes::FOOD_TYPE type = static_cast<ItemTypes::FOOD_TYPE>(i);
		std::string name = ItemTypes::FOOD_STRING_TO_ENUM_MAP.at(type);
		auto parameterFood = std::make_unique<ParameterItemFood>();
		parameterFood->LoadParameter(jsonParameterMap, name);
		templateFoodParameterMap_.emplace(type, std::move(parameterFood));
	}

	// お宝情報生成
	for (int i = 0; i < ItemTypes::TREASURE_TYPE_MAX; i++)
	{
		ItemTypes::TREASURE_TYPE type = static_cast<ItemTypes::TREASURE_TYPE>(i);
		std::string name = ItemTypes::TREASURE_STRING_TO_ENUM_MAP.at(type);
		auto parameterTreasure = std::make_unique<ParameterItemTreasure>();
		parameterTreasure->LoadParameter(jsonParameterMap, name);
		parameterTreasure->type_ = type;
		templateTreasureParameterMap_.emplace(type, std::move(parameterTreasure));
	}

	// お金の情報生成
	for (int i = 0; i < ItemTypes::MONEY_TYPE_MAX; i++)
	{
		ItemTypes::MONEY_TYPE type = static_cast<ItemTypes::MONEY_TYPE>(i);
		std::string name = ItemTypes::MONEY_STRING_TO_ENUM_MAP.at(type);
		auto parameterMoney = std::make_unique<ParameterItemMoney>();
		parameterMoney->LoadParameter(jsonParameterMap, name);
		templateMoneyParameterMap_.emplace(type, std::move(parameterMoney));
	}

	// ポーションの情報生成
	for (int i = 0; i < ItemTypes::POTION_TYPE_MAX; i++)
	{
		ItemTypes::POTION_TYPE type = static_cast<ItemTypes::POTION_TYPE>(i);
		std::string name = ItemTypes::POTION_STRING_TO_ENUM_MAP.at(type);
		auto parameterPotion = std::make_unique<ParameterItemPotion>();
		parameterPotion->LoadParameter(jsonParameterMap, name);
		templatePotionParameterMap_.emplace(type, std::move(parameterPotion));
	}
}