#include "../../Manager/Common/InputManager.h"
#include "../../Manager/Game/CollisionManager.h"
#include "../../Object/Character/Player.h"
#include "../../Object/ActorBase.h"
#include "../../Object/Common/Animation.h"
#include "../../Collider/ColliderCircle.h"
#include "ComponentStatePlayerAttack.h"

ComponentStatePlayerAttack::ComponentStatePlayerAttack(Player& owner) :
	ComponentCharacterStateBase(owner),
	owner_(owner),
	parameter_(owner.GetParameter()),
	ATTACK_START_FRAME(owner.GetParameter().defaultAttackStartFrame_),
	ATTACK_SECOND_FRAME(owner.GetParameter().defaultAttackSecondFrame_),
	ATTACK_DISTANCE(owner.GetParameter().defaultAttackDistance_),
	inputManager_(InputManager::GetInstance())
{
	attackPos_ = {};
	isAttack_ = false;
	isAttackSecond_ = false;
	isInputAttackSecond_ = false;
	collider_ = std::make_shared<ColliderCircle>(owner_, parameter_.attackCollisionTag_, attackPos_, parameter_.defaultAttackRadius_);
	collider_->SetIsActive(false);

	CollisionManager::GetInstance().Add(collider_);
}

ComponentStatePlayerAttack::~ComponentStatePlayerAttack()
{
	if (collider_)
	{
		collider_->Delete();
		collider_ = nullptr;
	}
}

void ComponentStatePlayerAttack::Init()
{
	collider_->SetIsActive(false);
	isAttack_ = false;
	isAttackSecond_ = false;
	isInputAttackSecond_ = false;
}

void ComponentStatePlayerAttack::Update()
{
	Animation& animation = owner_.GetAnimation();

	// 攻撃開始フレームの場合
	if (!isAttack_ && animation.GetAnimationIndex() >= ATTACK_START_FRAME)
	{
		// コライダーを活動状態へ
		collider_->SetIsActive(true);
		isAttack_ = true;
	}
	// 最初の攻撃中に入力を行った場合
	else if (inputManager_.IsTrgDown(InputManager::TYPE::PLAYER_ATTACK) && animation.GetAnimationIndex() < ATTACK_SECOND_FRAME)
	{
		// 二回目の攻撃を開始
		isInputAttackSecond_ = true;
	}
	// 二回目の攻撃フレームの場合
	else if (!isInputAttackSecond_ && animation.GetAnimationIndex() >= ATTACK_SECOND_FRAME - 1)
	{
		// 攻撃後の処理
		AttackEnd();
		return;
	}		
	// 二回目の攻撃フレームの場合
	else if (!isAttackSecond_ && animation.GetAnimationIndex() >= ATTACK_SECOND_FRAME - 1)
	{
		// コライダーを活動状態へ
		collider_->SetIsActive(true);
		isAttackSecond_ = true;
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
	AttackEnd();
}

void ComponentStatePlayerAttack::Remove()
{
	if (collider_)
	{
		collider_->Delete();
		collider_ = nullptr;
	}
}

void ComponentStatePlayerAttack::AttackEnd()
{
	// 攻撃後の処理
	owner_.AttackAfter();

	// コライダーの判定を一時消す
	collider_->SetIsActive(false);

	// 攻撃判定をなくす
	isAttack_ = false;
	parameter_.isAction_ = false;
}