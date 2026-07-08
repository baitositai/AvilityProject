#pragma once
#include <string>
#include <unordered_map>

class ItemTypes
{
public:

	enum class TYPE
	{
		AVILITY,	// アビリティ
		FOOD,		// 食べ物
		TREASURE,	// 宝
		MONEY,		// お金
		POTION,		// ポーション
		MAX
	};

	// 食べ物
	enum class FOOD_TYPE
	{
		FRIED_EGG,
		WAFFLE,
		PINEAPPLE,
		BACON,
		BEER,
		STEAK,
		CHEESE,
		ROASTED_CHICKEN,
		BREAD,
		EGGPLANT,
		RED_CHILI,
		GREEN_CHILI,
		TOMATO,
		STRAWBERRY,
		APPLE,
		KIWI,
		PUMPKIN_PIE,
		CHEESECAKE,
		PRETZEL,
		SALAMI,
		SALMON_FILLET,
		HONEY_JAR,
		JERKY,
		POTATO,
		WATERMELON,
		PANCAKES,
		CHICKEN_LEG,
		CHERRY,
		CHOCOLATE,
		SODA_CAN,
		AVOCADO,
		MEAT_SLICE,
		SHRIMP,
		OLIVE,
		PICKLES_JAR,
		BAKED_POTATO,
		MAX
	};

	// 宝
	enum class TREASURE_TYPE
	{
		BECKONING_CAT,
		TV,
		TIN_ROBOT,
		CLAY_WORK,
		BOTTLE_SHIP,
		STUFFED_TOY,
		POT,
		MAX
	};

	// お金
	enum class MONEY_TYPE
	{
		COIN,
		COIN_BAG,
		MAX
	};

	// ポーション種類
	enum class POTION_TYPE
	{
		ATTACK_UP,
		HPMAX_UP,
		SPEED_UP,
		MAX
	};

	// 食べ物の最大数
	static constexpr int FOOD_TYPE_MAX = static_cast<int>(FOOD_TYPE::MAX);

	// お宝の最大数
	static constexpr int TREASURE_TYPE_MAX = static_cast<int>(TREASURE_TYPE::MAX);

	// お金の最大数
	static constexpr int MONEY_TYPE_MAX = static_cast<int>(MONEY_TYPE::MAX);

	// ポーション最大数
	static constexpr int POTION_TYPE_MAX = static_cast<int>(POTION_TYPE::MAX);

	// 食べ物の列挙型からstring型へ変換する用のマップ
	static const std::unordered_map<FOOD_TYPE, std::string> FOOD_STRING_TO_ENUM_MAP;

	// お宝の列挙型からstring型へ変換する用のマップ
	static const std::unordered_map<TREASURE_TYPE, std::string> TREASURE_STRING_TO_ENUM_MAP;

	// お金の列挙型からstring型へ変換する用のマップ
	static const std::unordered_map<MONEY_TYPE, std::string> MONEY_STRING_TO_ENUM_MAP;

	// ポーションの列挙型からstringへ変換する用のマップ
	static const std::unordered_map<POTION_TYPE, std::string> POTION_STRING_TO_ENUM_MAP;
};