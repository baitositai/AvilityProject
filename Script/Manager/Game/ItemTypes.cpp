#include "ItemTypes.h"

const std::unordered_map<ItemTypes::FOOD_TYPE, std::string> ItemTypes::FOOD_STRING_TO_ENUM_MAP =
{
	{ItemTypes::FOOD_TYPE::FRIED_EGG, "friedEgg"},
	{ItemTypes::FOOD_TYPE::WAFFLE, "waffle"},
	{ItemTypes::FOOD_TYPE::PINEAPPLE, "pineapple"},
	{ItemTypes::FOOD_TYPE::BACON, "bacon"},
	{ItemTypes::FOOD_TYPE::BEER, "beer"},
	{ItemTypes::FOOD_TYPE::STEAK, "steak"},
	{ItemTypes::FOOD_TYPE::CHEESE, "cheese"},
	{ItemTypes::FOOD_TYPE::ROASTED_CHICKEN, "roastedChicken"},
	{ItemTypes::FOOD_TYPE::BREAD, "bread"},
	{ItemTypes::FOOD_TYPE::EGGPLANT, "eggplant"},
	{ItemTypes::FOOD_TYPE::RED_CHILI, "redChili"},
	{ItemTypes::FOOD_TYPE::GREEN_CHILI, "greenChili"},
	{ItemTypes::FOOD_TYPE::TOMATO, "tomato"},
	{ItemTypes::FOOD_TYPE::STRAWBERRY, "strawberry"},
	{ItemTypes::FOOD_TYPE::APPLE, "apple"},
	{ItemTypes::FOOD_TYPE::KIWI, "kiwi"},
	{ItemTypes::FOOD_TYPE::PUMPKIN_PIE, "pumpkinPie"},
	{ItemTypes::FOOD_TYPE::CHEESECAKE, "cheesecake"},
	{ItemTypes::FOOD_TYPE::PRETZEL, "pretzel"},
	{ItemTypes::FOOD_TYPE::SALAMI, "salami"},
	{ItemTypes::FOOD_TYPE::SALMON_FILLET, "salmonFillet"},
	{ItemTypes::FOOD_TYPE::HONEY_JAR, "honeyJar"},
	{ItemTypes::FOOD_TYPE::JERKY, "jerky"},
	{ItemTypes::FOOD_TYPE::POTATO, "potato"},
	{ItemTypes::FOOD_TYPE::WATERMELON, "watermelon"},
	{ItemTypes::FOOD_TYPE::PANCAKES, "pancakes"},
	{ItemTypes::FOOD_TYPE::CHICKEN_LEG, "chickenLeg"},
	{ItemTypes::FOOD_TYPE::CHERRY, "cherry"},
	{ItemTypes::FOOD_TYPE::CHOCOLATE, "chocolate"},
	{ItemTypes::FOOD_TYPE::SODA_CAN, "sodaCan"},
	{ItemTypes::FOOD_TYPE::AVOCADO, "avocado"},
	{ItemTypes::FOOD_TYPE::MEAT_SLICE, "meatSlice"},
	{ItemTypes::FOOD_TYPE::SHRIMP, "shrimp"},
	{ItemTypes::FOOD_TYPE::OLIVE, "olive"},
	{ItemTypes::FOOD_TYPE::PICKLES_JAR, "picklesJar"},
	{ItemTypes::FOOD_TYPE::BAKED_POTATO, "baked_potato"}
};

const std::unordered_map<ItemTypes::TREASURE_TYPE, std::string> ItemTypes::TREASURE_STRING_TO_ENUM_MAP =
{
	{ItemTypes::TREASURE_TYPE::BECKONING_CAT, "beckoningCat"},
	{ItemTypes::TREASURE_TYPE::TV, "tv"},
	{ItemTypes::TREASURE_TYPE::TIN_ROBOT, "tinRobot"},
	{ItemTypes::TREASURE_TYPE::CLAY_WORK, "clayWork"},
	{ItemTypes::TREASURE_TYPE::BOTTLE_SHIP, "bottleShip"},
	{ItemTypes::TREASURE_TYPE::STUFFED_TOY, "stuffedToy"},
	{ItemTypes::TREASURE_TYPE::POT, "pot"}
};

const std::unordered_map<ItemTypes::MONEY_TYPE, std::string> ItemTypes::MONEY_STRING_TO_ENUM_MAP =
{
	{ItemTypes::MONEY_TYPE::COIN, "coin"},
	{ItemTypes::MONEY_TYPE::COIN_BAG, "coinBag"}
};

const std::unordered_map<ItemTypes::POTION_TYPE, std::string> ItemTypes::POTION_STRING_TO_ENUM_MAP =
{
	{ItemTypes::POTION_TYPE::ATTACK_UP, "potionAttackUp"},
	{ItemTypes::POTION_TYPE::HPMAX_UP, "potionHpMaxUp"},
	{ItemTypes::POTION_TYPE::SPEED_UP, "potionSpeedUp"}
};