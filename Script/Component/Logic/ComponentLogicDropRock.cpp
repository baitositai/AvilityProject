#include "../../Application.h"
#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Game/CollisionManager.h"
#include "../../Manager/Game/GimmickManager.h"
#include "../../Manager/Game/PlayerManager.h"
#include "../../Collider/ColliderCircle.h"
#include "../../Object/Character/Enemy/EnemyGaiaGolem.h"
#include "../../Object/Gimmick/GimmickDropRock.h"
#include "../../Object/Gimmick/GimmickGroundRock.h"
#include "../../Object/Common/Animation.h"
#include "ComponentLogicDropRock.h"

ComponentLogicDropRock::ComponentLogicDropRock(EnemyGaiaGolem& owner):
	ComponentLogicBase(owner),
	owner_(owner),
	parameter_(owner_.GetParameter()),
	attackPos_({})
{
}

ComponentLogicDropRock::~ComponentLogicDropRock()
{
}

void ComponentLogicDropRock::Create()
{
	// //攻撃用コライダーの登録
	//// コライダーを複製して攻撃コライダーとして登録
	//// 攻撃用コライダーの登録
	attackCollider_ = std::make_shared<ColliderCircle>(owner_, parameter_.attackCollisionTag_, attackPos_, parameter_.defaultAttackRadius_);
	attackCollider_->SetIsActive(false);
	collisionManager_.Add(attackCollider_);
}

void ComponentLogicDropRock::Init()
{
	ComponentLogicBase::Init();

	//待機アニメーション
	owner_.GetAnimation().Play(Animation::TYPE::ATTACK,false);
	int createRockNum = ROCK_CREATE_NUM_MIN;
	const int playerNum = playerManager_.GetPlayerNum();
	std::vector<Vector2F> playersPos = playerManager_.GetPlayersPos();

	// 攻撃のコライダー設定
	attackCollider_->SetIsActive(true);

	std::vector<float>rockPosX;
	if (playerNum > ROCK_CREATE_NUM_MIN)createRockNum = playerNum;
	for (int i = 0; i < createRockNum; i++)
	{
		//岩生成
		GimmickManager::CreateParameter createParameter = {};
		createParameter.type = GimmickTypes::TYPE::GROUND_ROCK;

		createParameter.pos.y = ROCK_POS_Y;
		if (i < playerNum) { createParameter.pos.x = playersPos[i].x; }
		else { createParameter.pos.x = SetRandomPosX(rockPosX); }

		rockPosX.push_back(createParameter.pos.x);

		createParameter.attackPower = ATTACK_POINT;
		gimmickManager_.Create(createParameter);
	}
}

void ComponentLogicDropRock::Update()
{
	Animation& animation = owner_.GetAnimation();
	Vector2F dir = Vector2F::MulVector2FFloat(parameter_.GetFront(), parameter_.scale_);
	attackPos_ = Vector2F::AddVector2F(parameter_.pos_, Vector2F::MulVector2FFloat(dir, parameter_.defaultAttackDistance_));
	if (!animation.IsPlay())
	{
		isEnd_ = true;
		attackCollider_->SetIsActive(false);
	}
}

void ComponentLogicDropRock::Remove()
{
}

void ComponentLogicDropRock::AttackReset()
{
}

float ComponentLogicDropRock::SetRandomPosX(const std::vector<float>rockPosX)
{
	float ret = 0.0f;
	int min = BOSS_ROOM_RIGHT_X + ROCK_SIZE;
	int max = Application::SCREEN_SIZE_X - ROCK_SIZE - BOSS_ROOM_RIGHT_X;

	ret = min + std::rand() % (max - min);

	//ランダムで与えた値が別の岩と重なっていたらもう一度繰り返す
	if (IsRangeDropRock(rockPosX, ret))
	{
		return SetRandomPosX(rockPosX);
	}
	return ret;
}

const bool ComponentLogicDropRock::IsRangeDropRock(std::vector<float>rockPosX,float currentPosX)
{
	//岩の一つでも重なっていたらtrueを返す
	for (const float posX : rockPosX)
	{
		float overLap = std::abs(currentPosX - posX);
		if (overLap < ROCK_SIZE * 2)
		{
			return true;
		}
	}

	//どれとも重なっていなければfalseを返す
	return false;
}
