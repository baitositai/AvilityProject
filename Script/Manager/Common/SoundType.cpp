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
	{"seDecision", SoundType::SE::DECISION},
	{"seAbilityShotCharge", SoundType::SE::ABILITY_SHOT_CHARGE},
	{"seAbilityShotStart", SoundType::SE::ABILITY_SHOT_START},
	{"seAbilityStampCharge", SoundType::SE::ABILITY_STAMP_CHARGE},
	{"seAbilityStampLanding", SoundType::SE::ABILITY_STAMP_LANDING},
	{"seAbilityTeleportEnter", SoundType::SE::ABILITY_TELEPORT_ENTER},
	{"seAbilityTeleportExit", SoundType::SE::ABILITY_TELEPORT_EXIT},
	{"seAbilityGravityChange", SoundType::SE::ABILITY_GRAVITY_CHANGE},
	{"seAirSlash", SoundType::SE::AIRSLASH},
	{"seApplause", SoundType::SE::APPLAUSE},
	{"seCancel", SoundType::SE::CANCEL},
	{"seCheers", SoundType::SE::CHEERS},
	{"seGetAbility", SoundType::SE::GET_ABILITY},
	{"seGetMoney", SoundType::SE::GET_MONEY},
	{"seGetPotion", SoundType::SE::GET_POTION},
	{"seGetTreasure", SoundType::SE::GET_TREASURE},
	{"seHeal", SoundType::SE::HEAL},
	{"seJump", SoundType::SE::JUMP},
	{"seJumpLanding", SoundType::SE::JUMP_LANDING},
	{"seJumpSecond", SoundType::SE::JUMP_SECOND},
	{"sePlayerAttackHit", SoundType::SE::PLAYER_ATTACK_HIT},
	{"sePlayerDamage", SoundType::SE::PLAYER_DAMAGE},
	{"sePlayerDead", SoundType::SE::PLAYER_DEAD},
	{"seSwingAxe1", SoundType::SE::SWING_AXE1},
	{"seSwingAxe2", SoundType::SE::SWING_AXE2},
	{"seThrow", SoundType::SE::THROW},
	{"seGrowingBamboo", SoundType::SE::GROWING_BAMBOO},
	{"seOpenTreasureBox", SoundType::SE::OPEN_TREASURE_BOX},
	{"seDead", SoundType::SE::DEAD},
	{"seEventStart", SoundType::SE::EVENT_START},
	{"seDoor", SoundType::SE::DOOR}
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