#include "../../../Manager/Game/CollisionManager.h"
#include "../../../Object/Character/Player.h"
#include "../../../Object/ActorBase.h"
#include "../Collider/ColliderCircle.h"
#include "ComponentStatePlayerAttack.h"

ComponentStatePlayerAttack::ComponentStatePlayerAttack(Player& owner) :
	owner_(owner),
	ComponentCharacterStateBase(owner)
{
	attackPos_ = {};
	isAttack_ = false;
	collider_ = std::make_shared<ColliderCircle>(owner_, CollisionTags::TAG::PLAYER_ATTACK_NORMAL, attackPos_, 30.0f);
	collider_->SetIsActive(false);

	CollisionManager::GetInstance().Add(collider_);
}

ComponentStatePlayerAttack::~ComponentStatePlayerAttack()
{
}

void ComponentStatePlayerAttack::Update()
{
	if (!isAttack_)
	{
		collider_->SetIsActive(true);
	}

	// 攻撃位置の調整
	float dir = owner_.GetParameter()->direction ? -1.0f : 1.0f;
	attackPos_ = Vector2F::AddVector2F(owner_.GetParameter()->pos, Vector2F(30.0f * dir, 0));

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

	collider_->SetIsActive(false);
}
