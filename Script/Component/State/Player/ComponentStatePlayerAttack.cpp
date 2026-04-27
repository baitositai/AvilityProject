#include "../../../Manager/Game/CollisionManager.h"
#include "../../../Object/Character/Player.h"
#include "../../../Object/ActorBase.h"
#include "../Collider/ColliderCircle.h"
#include "ComponentStatePlayerAttack.h"

ComponentStatePlayerAttack::ComponentStatePlayerAttack(Player& owner) :
	owner_(owner),
	DEFAULT_ATTACK_LOCAL_POS(owner.GetDefaultAttackLocalPos()),
	ComponentCharacterStateBase(owner)
{
	attackPos_ = {};
	isAttack_ = false;
	collider_ = std::make_shared<ColliderCircle>(owner_, CollisionTags::TAG::PLAYER_ATTACK_NORMAL, attackPos_, owner_.GetDefaultAttackRadius());
	collider_->SetIsActive(false);

	CollisionManager::GetInstance().Add(collider_);
}

ComponentStatePlayerAttack::~ComponentStatePlayerAttack()
{
}

void ComponentStatePlayerAttack::Update()
{
	if (!isAttack_ && owner_.GetParameterAnimation().animationIndex >= 33)
	{
		// コライダーを活動状態へ
		collider_->SetIsActive(true);
		isAttack_ = true;
	}

	// 攻撃位置の調整
	float dir = owner_.GetParameter()->direction ? -1.0f : 1.0f;
	attackPos_ = Vector2F::AddVector2F(owner_.GetParameter()->pos, Vector2F(DEFAULT_ATTACK_LOCAL_POS.x * dir, DEFAULT_ATTACK_LOCAL_POS.y));

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

	// アニメーション速度変更
	owner_.ResetAnimationSpeed();

	// コライダーの判定を一時消す
	collider_->SetIsActive(false);

	// 攻撃判定をなくす
	isAttack_ = false;
}
