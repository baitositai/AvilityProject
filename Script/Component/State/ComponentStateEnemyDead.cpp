#include "../../Manager/Common/SoundManager.h"
#include "../../Manager/Common/SpriteEffectManager.h"
#include "../../Object/Character/Enemy/EnemyBase.h"
#include "ComponentStateEnemyDead.h"

ComponentStateEnemyDead::ComponentStateEnemyDead(EnemyBase& owner) :
	ComponentCharacterStateBase(owner),
	owner_(owner)
{
	isPlaySe_ = false;
}

ComponentStateEnemyDead::~ComponentStateEnemyDead()
{
}

void ComponentStateEnemyDead::Init()
{
	isPlaySe_ = false;
}

void ComponentStateEnemyDead::Update()
{
	if (isPlaySe_)
	{
		soundManager_.PlaySe(SoundType::SE::DEAD);
		isPlaySe_ = true;
	}

	// 死亡アニメーションが終了した場合
	if (owner_.GetAnimation().GetType() == Animation::TYPE::DEAD &&
		!owner_.GetAnimation().IsPlay())
	{
		// アイテムのドロップ
		owner_.DropItem();

		// エフェクト再生
		ParameterEnemy& myParameter = owner_.GetParameter();
		SpriteEffectManager::CreateParameter parameter;
		parameter.pos = myParameter.pos_;
		parameter.direction = myParameter.direction_;
		parameter.angle = myParameter.angle_;
		parameter.resourceKey = "effectEnemyDead";
		parameter.animationSpeed = 0.3f;
		SpriteEffectManager::GetInstance().Create(parameter);

		// 所有者を消す
		owner_.Delete();
	}
}
