#include "../../../Object/Character/Player.h"
#include "ComponentStatePlayerAttack.h"

ComponentStatePlayerAttack::ComponentStatePlayerAttack(Player& owner) :
	owner_(owner),
	ComponentCharacterStateBase(owner)
{
}

ComponentStatePlayerAttack::~ComponentStatePlayerAttack()
{
}

void ComponentStatePlayerAttack::Update()
{
	// アニメーションパラメータ取得
	const auto& parameter = owner_.GetParameterAnimation();

	// 再生中の場合
	if (parameter.isPlay)
	{
		return;
	}

	// 状態遷移
	owner_.ChangeState(Player::STATE::ALIVE);

	// アニメーション変更
	owner_.ChangeAnimation(Player::ANIMATION::IDLE);
}
