#pragma once
#include <string>
#include <map>

class SoundType
{
public:

	// ƒTƒEƒ“ƒh‚Ìí—Ş
	enum class TYPE
	{
		NONE,
		BGM,
		SE,
	};

	// BGM‚Ìí—Ş
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

	// SE‚Ìí—Ş
	enum class SE
	{
		GAME_START,
		SELECT,
		TRAIN_WHISTLE,
		DECISION,
		MAX
	};

	// BGM‚Ìí—Ş‚ğŠÇ—
	static const std::map<std::string, BGM> KEY_BGM_MAP;

	// SE‚Ìí—Ş‚ğŠÇ—
	static const std::map<std::string, SE> KEY_SE_MAP;

	// stringŒ^‚ğ“üè‚·‚é
	static std::string GetStringFromBGM(const BGM bgmType);
	static std::string GetStringFromSE(const SE seType);
};