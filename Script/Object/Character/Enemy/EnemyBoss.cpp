#include "../../Manager/Game/UiManager.h"
#include "../../Ui/Enemy/UiBossHpBar.h"
#include "EnemyBoss.h"

EnemyBoss::EnemyBoss(std::unique_ptr<ParameterEnemy> parameter) :
	EnemyBase(std::move(parameter))
{
}

EnemyBoss::~EnemyBoss()
{
}

void EnemyBoss::InitUi()
{
	uiMng_.Add(std::move(std::make_unique<UiBossHpBar>(*this)));
}
