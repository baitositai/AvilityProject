#include "../../Manager/Game/UiManager.h"
#include "../../Ui/Enemy/UiBossHpBar.h"
#include "EnemyBoss.h"

EnemyBoss::EnemyBoss(std::unique_ptr<ParameterEnemyBoss> parameter) :
	EnemyBase(std::move(parameter))
{
	// ƒpƒ‰ƒ[ƒ^î•ñ
	parameterEnemyBoss_ = dynamic_cast<ParameterEnemyBoss*>(GetParameterEnemyPtr());
	assert(parameterEnemyBoss_ != nullptr);
}

EnemyBoss::~EnemyBoss()
{
}

void EnemyBoss::InitUi()
{
	uiMng_.Add(std::move(std::make_unique<UiBossHpBar>(*this)));
}
