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
	// 死亡アニメーション終了後かつ所有者がプレイヤー以外の場合
	if (owner_.GetType() != CharacterBase::TYPE::PLAYER &&
		owner_.GetAnimation().GetType() == Animation::TYPE::DEAD &&
		!owner_.GetAnimation().IsPlay())
	{
		// 所有者を消す
		owner_.Delete();
	}
}
