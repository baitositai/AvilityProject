#pragma once

class EnemyTypes
{
public:

	// 種類
	enum class TYPE
	{
		CLONE,
		SLIME,
		MUSHROOM,
		HAT,
		SNAKE,
		SAMURAI,
		
		// ボス
		MAID,
		PANDA,
		GAIA_GOLEM,

		MAX,
	};

	// 最大数
	static constexpr int MAX = static_cast<int>(TYPE::MAX);

	// 雑魚敵数
	static constexpr int WEAK_MAX = static_cast<int>(TYPE::MAID);

	// ボス総数
	static constexpr int BOSS_MAX = 3;

	// ボスのリスト
	static constexpr TYPE BOSS_LIST[BOSS_MAX] = {
		TYPE::MAID,
		TYPE::PANDA,
		TYPE::GAIA_GOLEM
	};

	// ボス種類をランダムで決定する
	static TYPE GetRandomBossType();
};