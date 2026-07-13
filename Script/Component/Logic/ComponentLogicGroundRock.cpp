#include "../../Application.h"
#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Game/CollisionManager.h"
#include "../../Manager/Game/GimmickManager.h"
#include "../../Manager/Game/PlayerManager.h"
#include "../../Collider/ColliderCircle.h"
#include "../../Object/Character/Enemy/EnemyGaiaGolem.h"
#include "../../Object/Gimmick/GimmickDropRock.h"
#include "../../Object/Common/Animation.h"
#include "ComponentLogicGroundRock.h"

ComponentLogicGroundRock::ComponentLogicGroundRock(EnemyGaiaGolem& owner):
	ComponentLogicBase(owner),
	owner_(owner),
	parameter_(owner_.GetParameter()),
	attackPos_({})
{
}

ComponentLogicGroundRock::~ComponentLogicGroundRock()
{
}

void ComponentLogicGroundRock::Create()
{
	// //攻撃用コライダーの登録
	//// コライダーを複製して攻撃コライダーとして登録
	//// 攻撃用コライダーの登録
	attackCollider_ = std::make_shared<ColliderCircle>(owner_, parameter_.attackCollisionTag_, attackPos_, parameter_.defaultAttackRadius_);
	attackCollider_->SetIsActive(false);
	collisionManager_.Add(attackCollider_);
}

void ComponentLogicGroundRock::Init()
{
	ComponentLogicBase::Init();
	isCreateGroundRock_ = false;

	//待機アニメーション
	owner_.GetAnimation().Play(Animation::TYPE::ATTACK_2, false);
	int createRockNum = ROCK_CREATE_NUM_MIN;
	const int playerNum = playerManager_.GetPlayerNum();
	std::vector<Vector2F> playersPos = playerManager_.GetPlayersPos();

	// 攻撃のコライダー設定
	attackCollider_->SetIsActive(true);
}

void ComponentLogicGroundRock::Update()
{
	Animation& animation = owner_.GetAnimation();
	Vector2F dir = Vector2F::MulVector2FFloat(parameter_.GetFront(), parameter_.scale_);
	attackPos_ = Vector2F::AddVector2F(parameter_.pos_, Vector2F::MulVector2FFloat(dir, parameter_.defaultAttackDistance_));
	if (!animation.IsPlay())
	{
		isEnd_ = true;
		attackCollider_->SetIsActive(false);
	}
	//一定のアニメーションインデックスになったら
	else if (animation.GetAnimationIndex()== CREATE_GROUNDROCK_INDEX)
	{
		CreateGroundRock();
	}
}

void ComponentLogicGroundRock::Remove()
{
}

void ComponentLogicGroundRock::AttackReset()
{
}

void ComponentLogicGroundRock::CreateGroundRock(void)
{
	//すでに生成していたら処理を飛ばす
	if (isCreateGroundRock_)return;

	for (int i = 0; i < ROCK_CREATE_NUM_MIN; i++)
	{
		//岩生成
		GimmickManager::CreateParameter createParameter = {};
		createParameter.type = GimmickTypes::TYPE::GROUND_ROCK;
		Vector2F enemyPos = owner_.GetParameter().pos_;
		createParameter.pos = attackPos_;
		createParameter.attackPower = ATTACK_POINT;
		createParameter.moveDir = parameter_.direction_ ? Vector2F(-1.0f, 0.0f) : Vector2F(1.0f, 0.0f);
		gimmickManager_.Create(createParameter);
	}
	isCreateGroundRock_ = true;
}
