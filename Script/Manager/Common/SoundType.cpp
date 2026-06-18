#include "SoundType.h"

// •¶Žš—ñ‚©‚çenum ‚Ì‘Î‰ž•\
const std::map<std::string, SoundType::BGM> SoundType::KEY_BGM_MAP =
{
	{"bgmTitle",SoundType::BGM::TITLE},
	{"bgmTrain", SoundType::BGM::TRAIN},
	{"bgmTrainRoom", SoundType::BGM::TRAIN_ROOM},
	{"bgmGame1", SoundType::BGM::GAME1},
	{"bgmGame2", SoundType::BGM::GAME2},
	{"bgmGame3", SoundType::BGM::GAME3},
	{"bgmGame4", SoundType::BGM::GAME4},
	{"bgmGame5", SoundType::BGM::GAME5},
	{"bgmResult", SoundType::BGM::RESULT}
};

const std::map<std::string, SoundType::SE> SoundType::KEY_SE_MAP =
{
    {"seGameStart", SoundType::SE::GAME_START},
	{"seSelect", SoundType::SE::SELECT},
	{"seTrainWhistle", SoundType::SE::TRAIN_WHISTLE},
	{"seDecision", SoundType::SE::DECISION}
};