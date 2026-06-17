#pragma once
#include <memory>
#include <functional>
#include <unordered_map>
#include <vector>
#include "../../Manager/Game/ItemTypes.h"
#include "../../Component/Avility/AvilityTypes.h"
#include "../../Common/Vector2F.h"

class ItemBase;
class ItemAvility;
class ItemFood;
class ItemTreasure;
class ItemMoney;

class ParameterItemAvility;
class ParameterItemFood;
class ParameterItemTreasure;
class ParameterItemMoney;

class PlayerManager;

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
	/// <param name="moneyAmount">金額</param>
	/// <returns>コイン</returns>
	std::vector<std::unique_ptr<ItemMoney>> CreateMonies(const int moneyAmount, const Vector2F& pos);

	/// <summary>
	/// 宝箱用の複数アイテムを生成
	/// </summary>
	/// <returns>宝箱用アイテム</returns>
	std::vector<std::unique_ptr<ItemBase>> CreateTreasureChestItemList(const Vector2F& terasureChestPos);
	
	/// <summary>
	/// パラメーター関係の初期化
	/// </summary>
	void InitParameter();

private:

	const std::vector<int> CREATE_MONEIES = { 3000, 3500, 4000, 4500, 5000 };
	const Vector2F RANGE = { 120.0f, 30.0f };
	const Vector2F OFFSET = { 60.0f, 15.0f };
	const Vector2F KNOCK_BACK_POWER_MIN = { 200, 600 };
	const Vector2F KNOCK_BACK_POWER_MAX = { 400, 800 };

	// 各種アイテムのテンプレートとなるパラメータマップ
	std::unordered_map<AvilityTypes::TYPE, std::unique_ptr<ParameterItemAvility>> templateAvilityParameterMap_;
	std::unordered_map<ItemTypes::FOOD_TYPE, std::unique_ptr<ParameterItemFood>> templateFoodParameterMap_;
	std::unordered_map<ItemTypes::TREASURE_TYPE, std::unique_ptr<ParameterItemTreasure>> templateTreasureParameterMap_;
	std::unordered_map<ItemTypes::MONEY_TYPE, std::unique_ptr<ParameterItemMoney>> templateMoneyParameterMap_;

	// プレイヤー管理の参照
	PlayerManager& playerManager_;
};