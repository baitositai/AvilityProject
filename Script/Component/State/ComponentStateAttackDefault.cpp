#include "../../Manager/Game/CollisionManager.h"
#include "../../Object/Character/Player.h"
#include "../../Object/ActorBase.h"
#include "../../Object/Common/Animation.h"
#include "../Collider/ColliderCircle.h"
#include "ComponentStateAttackDefault.h"

ComponentStateAttackDefault::ComponentStateAttackDefault(CharacterBase& owner) :
	owner_(owner),
	parameter_(owner.GetParameter()),
	ATTACK_DISTANCE(owner.GetParameter().defaultAttackDistance_),
	ATTACK_START_FRAME(owner.GetParameter().defaultAttackStartFrame_),
	ComponentCharacterStateBase(owner)
{
	attackPos_ = {};
	isAttack_ = false;
	collider_ = std::make_shared<ColliderCircle>(owner_, parameter_.attackCollisionTag_, attackPos_, parameter_.defaultAttackRadius_);
	collider_->SetIsActive(false);

	CollisionManager::GetInstance().Add(collider_);
}

ComponentStateAttackDefault::~ComponentStateAttackDefault()
{
	if (collider_)
	{
		collider_->Delete();
		collider_ = nullptr;
	}
}

void ComponentStateAttackDefault::Init()
{
	collider_->SetIsActive(false);
	isAttack_ = false;
}

void ComponentStateAttackDefault::Update()
{
	Animation& animation = owner_.GetAnimation();

	if (!isAttack_ && animation.GetAnimationIndex() >= ATTACK_START_FRAME)
	{
		// コライダーを活動状態へ
		collider_->SetIsActive(true);
		isAttack_ = true;
	}

	// 攻撃者の前方向を取得
	Vector2F dir = Vector2F::MulVector2FFloat(parameter_.GetFront(), parameter_.scale_);
	attackPos_ = Vector2F::AddVector2F(parameter_.pos_, Vector2F::MulVector2FFloat(dir, ATTACK_DISTANCE));

	// 再生中の場合
	if (animation.IsPlay())
	{
		return;
	}

	// 攻撃後の処理
	owner_.AttackAfter();

	// コライダーの判定を一時消す
	collider_->SetIsActive(false);

	// 攻撃判定をなくす
	isAttack_ = false;
}

void ComponentStateAttackDefault::Remove()
{
	if (collider_)
	{
		collider_->Delete();
		collider_ = nullptr;
	}
}