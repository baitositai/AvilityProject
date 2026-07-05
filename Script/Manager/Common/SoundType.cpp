#include "SoundType.h"

// 文字列からenum の対応表
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

std::string SoundType::GetStringFromBGM(BGM bgmType)
{
    // マップの中身をループして一致する値を探す
    for (const auto& pair : KEY_BGM_MAP)
    {
        if (pair.second == bgmType)
        {
            return pair.first;
        }
    }
    return "";
}

std::string SoundType::GetStringFromSE(SE seType)
{
    // マップの中身をループして一致する値を探す
    for (const auto& pair : KEY_SE_MAP)
    {
        if (pair.second == seType)
        {
            return pair.first;
        }
    }
    return "";
}