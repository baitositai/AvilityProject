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
		
		// ƒ{ƒX
		MAID,
		PANDA,

		MAX,
	};

	// Å‘å”
	static constexpr int MAX = static_cast<int>(TYPE::MAX);

	// G‹›“G”
	static constexpr int WEAK_MAX = static_cast<int>(TYPE::MAID);
};