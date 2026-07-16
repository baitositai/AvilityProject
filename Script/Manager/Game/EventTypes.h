#pragma once
#include <string>
#include <unordered_map>

class EventTypes
{
public:

	enum class TYPE
	{
		TARGET_DESTROY,
		TIME_LIMIT_DEFEAT_ALL,
		TREASURE_CHEST,
		MAX
	};

	static constexpr int TYPE_MAX = static_cast<int>(EventTypes::TYPE::MAX);
};

