#include "CollisionTags.h"

const std::map<CollisionTags::TAG, std::string> CollisionTags::TAG_NAME_MAP =
{
	{TAG::NONE, "none"},
	{TAG::PLAYER, "player"},
	{TAG::STAGE, "stage"},
	{TAG::ENEMY, "enemy"},
};