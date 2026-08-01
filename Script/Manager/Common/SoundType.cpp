#include <vector>
#include <DxLib.h>
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
	{"bgmBossBattleBamboo", SoundType::BGM::BOSS_BAMBOO},
	{"bgmBossBattleMaid", SoundType::BGM::BOSS_MAID},
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
	{"seDoor", SoundType::SE::DOOR},
	{"seDisplayExplanation", SoundType::SE::DISPLAY_EXPLANATION },
	{"seAlarm", SoundType::SE::ALARM},
	{"seRockDestroy", SoundType::SE::ROCK_DESTROY},
	{"seBossDestroy", SoundType::SE::BOSS_DESTROY},
	{"seRapidFire", SoundType::SE::RAPID_FIRE},
	{"sePlayerRespawn", SoundType::SE::PLAYER_RESPAWN},
	{"seFailue", SoundType::SE::FAILUE},
	{"seTreasureBox", SoundType::SE::TREASURE_BOX},
	{"seRank", SoundType::SE::RANK},
	{"seGameParticipation", SoundType::SE::GAME_PARTICIPATION},
	{"seGameLeave", SoundType::SE::GAME_LEAVE},
	{"seTextAnimation", SoundType::SE::TEXT_ANIMATION},
	{"seShopEnter", SoundType::SE::SHOP_ENTER},
	{"sePurchase", SoundType::SE::PURCHASE},
	{"seGolemAttack", SoundType::SE::GOLEM_ATTACK},
	{"seReady", SoundType::SE::READY},
	{"seGo", SoundType::SE::GO},
	{"seGong", SoundType::SE::GONG},
	{"seSwordsClash", SoundType::SE::SWORDS_CLASH},
	{"seTargetDestroy", SoundType::SE::TARGET_DESTROY},
	{"seDrumRoll", SoundType::SE::DRUM_ROLL},
	{"seDrumRollEnd", SoundType::SE::DRUM_ROLL_END},
	{"seBambooThrow", SoundType::SE::BAMBOO_THROW},
	{"seGameOver", SoundType::SE::GAME_OVER},
	{"seSuccess", SoundType::SE::SUCCESS}
};

const std::map<EnemyTypes::TYPE, SoundType::BGM> SoundType::BOSS_SOUND_MAP =
{
	{EnemyTypes::TYPE::GAIA_GOLEM, SoundType::BGM::BOSS_MAID },
	{EnemyTypes::TYPE::MAID, SoundType::BGM::BOSS_MAID },
	{EnemyTypes::TYPE::PANDA, SoundType::BGM::BOSS_BAMBOO },
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

const SoundType::BGM SoundType::GetRandomGameBgm()
{
	const std::vector<BGM> BGM_LIST =
	{
		BGM::GAME1,
		BGM::GAME2,
		BGM::GAME3,
		BGM::GAME4,
		BGM::GAME5
	};
	const int RANDOM_COUNT = GetRand(static_cast<int>(BGM_LIST.size()) - 1);
	return BGM_LIST[RANDOM_COUNT];
}