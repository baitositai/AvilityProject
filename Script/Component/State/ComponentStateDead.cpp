#include "../../Object/Character/CharacterBase.h"
#include "../../Object/Common/Animation.h"
#include "ComponentStateDead.h"

ComponentStateDead::ComponentStateDead(CharacterBase& owner) :
	ComponentCharacterStateBase(owner),
	owner_(owner)
{
}

ComponentStateDead::~ComponentStateDead()
{
}

void ComponentStateDead::Update()
{
	// プレイヤーの場合は処理を無視
	if(owner_.GetType() == CharacterBase::TYPE::PLAYER)
	{
		return;
	}

	// 死亡アニメーションが終了した場合
	if (owner_.GetAnimation().GetType() == Animation::TYPE::DEAD &&
		!owner_.GetAnimation().IsPlay())
	{
		// 所有者を消す
		owner_.Delete();
	}
}
