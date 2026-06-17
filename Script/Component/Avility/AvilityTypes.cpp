#include "AvilityTypes.h"

const std::unordered_map<AvilityTypes::TYPE, std::string> AvilityTypes::AVILITY_NAME_MAP =
{
	{AvilityTypes::TYPE::SHOT, "shot"},
	//{AvilityTypes::TYPE::BOX, "box"},
	{AvilityTypes::TYPE::STAMP, "stamp"},
	{AvilityTypes::TYPE::GRAVITYCONTROLL, "gravityControll"},
	{AvilityTypes::TYPE::TELEPORT, "teleport"},
	{AvilityTypes::TYPE::GIANT, "giant"},
	{AvilityTypes::TYPE::METAL, "metal"},
	{AvilityTypes::TYPE::AIRWALK, "airwalk"},
	{AvilityTypes::TYPE::AIRSLASH, "airslash"},
	{AvilityTypes::TYPE::SUPERMAN, "superman"}
};