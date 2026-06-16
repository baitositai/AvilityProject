#include "../Utility/UtilityLoad.h"
#include "../Object/Item/ItemAvility.h"
#include "../Object/Item/ItemCoin.h"
#include "../Object/Item/ItemCoinBag.h"
#include "../Object/Item/ItemFood.h"
#include "../Object/Item/ItemTreasure.h"
#include "ItemGenerator.h"

ItemGenerator::ItemGenerator()
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

std::unique_ptr<ItemCoin> ItemGenerator::CreateCoin()
{
	std::unique_ptr<ParameterItemMoney> parameter = std::make_unique<ParameterItemMoney>(*templeteCoinParameter_);
	std::unique_ptr<ItemCoin> item = std::make_unique<ItemCoin>(std::move(parameter));
    return item;
}

std::unique_ptr<ItemCoinBag> ItemGenerator::CreateCoinBag()
{
	std::unique_ptr<ParameterItemMoney> parameter = std::make_unique<ParameterItemMoney>(*templeteCoinBagParameter_);
	std::unique_ptr<ItemCoinBag> item = std::make_unique<ItemCoinBag>(std::move(parameter));
	return item;
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
		templateTreasureParameterMap_.emplace(type, std::move(parameterTreasure));
	}

	// コインの情報取得
	const auto& jsonCoinParameter = jsonParameterMap.at("coin").front();
	templeteCoinParameter_ = std::make_unique<ParameterItemMoney>();
	templeteCoinParameter_->LoadParameter(jsonCoinParameter);

	// コイン鞄の情報取得
	const auto& jsonCoinBagParameter = jsonParameterMap.at("coinBag").front();
	templeteCoinBagParameter_ = std::make_unique<ParameterItemMoney>();
	templeteCoinBagParameter_->LoadParameter(jsonCoinBagParameter);
}