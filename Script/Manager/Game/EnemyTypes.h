#pragma once

class EnemyTypes
{
public:

	// í—Ş
	enum class TYPE
	{
		CLONE,
		SLIME,
		MUSHROOM,
		HAT,
		SNAKE,
		SAMURAI,
		MAX,
	};

	// Å‘å”
	static constexpr int MAX = static_cast<int>(TYPE::MAX);
};