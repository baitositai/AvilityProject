#pragma once
#include <string>
#include <map>

class SoundType
{
public:

	// ÉTÉEÉìÉhÇÃéÌóﬁ
	enum class TYPE
	{
		NONE,
		BGM,
		SE,
	};

	// BGMÇÃéÌóﬁ
	enum class BGM
	{
		TITLE,
		TRAIN,
		TRAIN_ROOM,
		GAME1,
		GAME2,
		GAME3,
		GAME4,
		GAME5,
		RESULT,
		GAMEOVER,
		MAX
	};

	// SEÇÃéÌóﬁ
	enum class SE
	{
		GAME_START,
		SELECT,
		TRAIN_WHISTLE,
		DECISION,
		ABILITY_SHOT_CHARGE,
		ABILITY_SHOT_START,
		ABILITY_STAMP_CHARGE,
		ABILITY_STAMP_LANDING,
		ABILITY_TELEPORT_ENTER,
		ABILITY_TELEPORT_EXIT,
		ABILITY_GRAVITY_CHANGE,
		AIRSLASH,
		APPLAUSE,
		CANCEL,
		CHEERS,
		GET_ABILITY,
		GET_MONEY,
		GET_POTION,
		GET_TREASURE,
		HEAL,
		JUMP,
		JUMP_LANDING,
		JUMP_SECOND,
		PLAYER_ATTACK_HIT,
		PLAYER_DAMAGE,
		PLAYER_DEAD,
		SWING_AXE1,
		SWING_AXE2,
		THROW,
		GROWING_BAMBOO,
		OPEN_TREASURE_BOX,
		EVENT_START,
		DEAD,
		DOOR,
		MAX
	};

	// BGMÇÃéÌóﬁÇä«óù
	static const std::map<std::string, BGM> KEY_BGM_MAP;

	// SEÇÃéÌóﬁÇä«óù
	static const std::map<std::string, SE> KEY_SE_MAP;

	// stringå^Çì¸éËÇ∑ÇÈ
	static std::string GetStringFromBGM(const BGM bgmType);
	static std::string GetStringFromSE(const SE seType);
};