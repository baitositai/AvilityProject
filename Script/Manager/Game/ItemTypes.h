#pragma once
#include <string>
#include <unordered_map>

class ItemTypes
{
public:

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

	// 食べ物の最大数
	static constexpr int FOOD_TYPE_MAX = static_cast<int>(FOOD_TYPE::MAX);

	// お宝の最大数
	static constexpr int TREASURE_TYPE_MAX = static_cast<int>(TREASURE_TYPE::MAX);

	// 食べ物の列挙型からstring型へ変換する用のマップ
	static const std::unordered_map<FOOD_TYPE, std::string> FOOD_STRING_TO_ENUM_MAP;

	// お宝の列挙型からstring型へ変換する用のマップ
	static const std::unordered_map<TREASURE_TYPE, std::string> TREASURE_STRING_TO_ENUM_MAP;
};

