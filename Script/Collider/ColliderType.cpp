#include "ColliderType.h"

const std::map<ColliderType::TYPE, std::string> ColliderType::TYPE_NAME_MAP =
{
	{TYPE::NONE, "none"},
	{TYPE::BOX, "box"},
	{TYPE::LINE, "line"},
	{TYPE::CIRCLE, "circle"},
	{TYPE::ARRAY, "array"},
};