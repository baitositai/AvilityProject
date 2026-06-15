#pragma once
#include <string>
#include <unordered_map>

class EventTypes
{
public:

	enum class TYPE
	{
		TIME_LIMIT_DEFEAT_ALL,
		TARGET_DESTROY,
		TREASURE_CHEST,
		MAX
	};

	static constexpr int TYPE_MAX = static_cast<int>(EventTypes::TYPE::MAX);
};

