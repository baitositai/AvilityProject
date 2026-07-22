#include "../../Utility/UtilityCommon.h"
#include "EnemyTypes.h"

EnemyTypes::TYPE EnemyTypes::GetRandomBossType()
{
    const int randomIndex = UtilityCommon::GetRandomCount(BOSS_MAX - 1, 0);
    return BOSS_LIST[randomIndex];
}
