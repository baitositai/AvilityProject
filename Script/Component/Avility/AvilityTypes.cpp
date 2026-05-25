#include "AvilityTypes.h"

const std::unordered_map<AvilityTypes::TYPE, std::string> AvilityTypes::AVILITY_NAME_MAP =
{
	{AvilityTypes::TYPE::SHOT, "avilityShot"},
	{AvilityTypes::TYPE::BOX, "avilityBox"},
	{AvilityTypes::TYPE::STAMP, "avilityStamp"},
	{AvilityTypes::TYPE::GRAVITY, "avilityGravity"},
	{AvilityTypes::TYPE::TELEPORT, "avilityTeleport"},
	{AvilityTypes::TYPE::GIANT, "avilityGiant"},
	{AvilityTypes::TYPE::METAL, "avilityMetal"},
	{AvilityTypes::TYPE::AIRWALK, "avilityAirwalk"},
	{AvilityTypes::TYPE::AIRSLASH, "avilityAirslash"},
	{AvilityTypes::TYPE::SUPERMAN, "avilitySuperman"}
};