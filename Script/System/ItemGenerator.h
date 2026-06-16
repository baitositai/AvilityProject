#pragma once
#include <memory>
#include <functional>
#include <unordered_map>
#include "../../Manager/Game/ItemTypes.h"
#include "../../Component/Avility/AvilityTypes.h"

class ItemBase;
class ItemAvility;
class ItemFood;
class ItemTreasure;
class ItemCoin;
class ItemCoinBag;

class ParameterItemAvility;
class ParameterItemFood;
class ParameterItemTreasure;
class ParameterItemMoney;

class ItemGenerator
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ItemGenerator();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ItemGenerator();

	/// <summary>
	/// アビリティを生成
	/// </summary>
	/// <param name="type">種類</param>
	/// <returns>アビリティを返す</returns>
	std::unique_ptr<ItemAvility> CreateAvility(const AvilityTypes::TYPE type);

	/// <summary>
	/// 食べ物生成
	/// </summary>
	/// <param name="type">種類</param>
	/// <returns>食べ物返す</returns>
	std::unique_ptr<ItemFood> CreateFood(const ItemTypes::FOOD_TYPE type);

	/// <summary>
	/// お宝を生成する
	/// </summary>
	/// <param name="type">種類</param>
	/// <returns>お宝を返す</returns>
	std::unique_ptr<ItemTreasure> CreateTreasure(const ItemTypes::TREASURE_TYPE type);

	/// <summary>
	/// コインを生成
	/// </summary>
	/// <returns>コイン</returns>
	std::unique_ptr<ItemCoin> CreateCoin();

	/// <summary>
	/// コインバッグを生成
	/// </summary>
	/// <returns>コインバッグ</returns>
	std::unique_ptr<ItemCoinBag> CreateCoinBag();	
	
	/// <summary>
	/// パラメーター関係の初期化
	/// </summary>
	void InitParameter();

private:

	// 各種アイテムのテンプレートとなるパラメータマップ
	std::unordered_map<AvilityTypes::TYPE, std::unique_ptr<ParameterItemAvility>> templateAvilityParameterMap_;
	std::unordered_map<ItemTypes::FOOD_TYPE, std::unique_ptr<ParameterItemFood>> templateFoodParameterMap_;
	std::unordered_map<ItemTypes::TREASURE_TYPE, std::unique_ptr<ParameterItemTreasure>> templateTreasureParameterMap_;
	std::unique_ptr<ParameterItemMoney> templeteCoinParameter_;
	std::unique_ptr<ParameterItemMoney> templeteCoinBagParameter_;

};