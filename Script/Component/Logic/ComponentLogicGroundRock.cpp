#include "../../Application.h"
#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Common/Camera.h"
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
	attackPos_({}),
	camera_(SceneManager::GetInstance().GetCamera())
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
		camera_.SetCameraShake(CAMERA_SHAKE_TIME, CAMERA_SHAKE_POWER);
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

	std::array<int, ROCK_CREATE_NUM_MIN> horizontalSpd = { -1,-1 };
	for (int i = 0; i < ROCK_CREATE_NUM_MIN; i++)
	{
		//岩生成
		GimmickManager::CreateParameter createParameter = {};
		createParameter.type = GimmickTypes::TYPE::GROUND_ROCK;
		Vector2F enemyPos = owner_.GetParameter().pos_;
		createParameter.pos = attackPos_;
		createParameter.attackPower = ATTACK_POINT;
		horizontalSpd[i] = SetRandomHorizonSpd(horizontalSpd,i);
		horizontalSpd[i] = parameter_.direction_ ? horizontalSpd[i] : -horizontalSpd[i];
		gimmickManager_.CreateGroundRock(createParameter, horizontalSpd[i]);
	}
	isCreateGroundRock_ = true;
}

float ComponentLogicGroundRock::SetRandomHorizonSpd(std::array<int, ROCK_CREATE_NUM_MIN>& _horizonSpd, const int _createIndex)
{
	int randomSpd = 0.0f;
	//短距離から中距離の範囲に届くように速度を指定
	if (_createIndex == 0) 
	{ 
		randomSpd = JUMP_SPD_MIN + std::rand() % (static_cast<int>(JUMP_SPD_MID) - static_cast<int>(JUMP_SPD_MIN)); 
	}
	else
	{
		randomSpd = JUMP_SPD_MID + std::rand() % (static_cast<int>(JUMP_SPD_MAX) - static_cast<int>(JUMP_SPD_MID));
	}
	return static_cast<float>(randomSpd);
}
