#include "../../Manager/Common/SpriteEffectManager.h"
#include "../../Parameter/Character/Enemy/ParameterEnemyGaiaGolem.h"
#include "EnemyGaiaGolem.h"

EnemyGaiaGolem::EnemyGaiaGolem(std::unique_ptr<ParameterEnemyGaiaGolem> parameter):
	EnemyBoss(std::move(parameter))
{
	//専用のパラメータ
	parameterEnemyGaiaGolem_ = dynamic_cast<ParameterEnemyGaiaGolem*>(GetParameterEnemyBossPtr());
	assert(parameterEnemyGaiaGolem_ != nullptr);
}

EnemyGaiaGolem::~EnemyGaiaGolem()
{
}

void EnemyGaiaGolem::Update(void)
{
	//歩いた時に足元に煙エフェクトを出したい
	//if (animation_->GetAnimationIndex() == 10)
	//{
	//	SpriteEffectManager::GetInstance().
	//	SpriteEffectManager::CreateParameter effParameter = {};
	//	effParameter.pos = parameterEnemyGaiaGolem_->GetFootPos();
	//	effParameter.resourceKey = "rockLanding";
	//	effParameter.scale = parameterEnemyGaiaGolem_->scale_;
	//	SpriteEffectManager::GetInstance().Create(effParameter);
	//}

	EnemyBoss::Update();
}
