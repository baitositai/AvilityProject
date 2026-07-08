#include "../../Application.h"
#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Game/CollisionManager.h"
#include "../../Manager/Game/GimmickManager.h"
#include "../../Manager/Game/PlayerManager.h"
#include "../../Collider/ColliderCircle.h"
#include "../../Object/Character/Enemy/EnemyGaiaGolem.h"
#include "../../Object/Gimmick/GimmickDropRock.h"
#include "../../Object/Common/Animation.h"
#include "ComponentLogicDropRock.h"

ComponentLogicDropRock::ComponentLogicDropRock(EnemyGaiaGolem& owner):
	ComponentLogicBase(owner),
	owner_(owner),
	parameter_(owner_.GetParameter())
{
}

ComponentLogicDropRock::~ComponentLogicDropRock()
{
}

void ComponentLogicDropRock::Create()
{
	int createRockNum = ROCK_CREATE_NUM_MIN;
	const int playerNum = playerManager_.GetPlayerNum();
	std::vector<Vector2F> playersPos= playerManager_.GetPlayersPos();
	if (playerNum > ROCK_CREATE_NUM_MIN)createRockNum = playerNum;
	for (int i = 0; i < createRockNum; i++)
	{
		// 竹生成
		GimmickManager::CreateParameter createParameter = {};
		createParameter.type = GimmickTypes::TYPE::DROP_ROCK;

		createParameter.pos.y = ROCK_POS_Y;
		if (i < playerNum) { createParameter.pos.x = playersPos[i].x; }
		else { createParameter.pos.x = SetRandomPosX(); }
		createParameter.attackPower = 40;
		gimmickManager_.Create(createParameter);
	}
	// 待機アニメーション
	owner_.GetAnimation().Play(Animation::TYPE::ATTACK_2);

	// 攻撃用コライダーの登録
	//attackCollider_ = std::make_shared<ColliderCircle>(owner_, parameter_.attackCollisionTag_, attackPos_, parameter_.defaultAttackRadius_);
	//attackCollider_->SetIsActive(false);
	//collisionManager_.Add(attackCollider_);
}

void ComponentLogicDropRock::Init()
{
}

void ComponentLogicDropRock::Update()
{
	Animation& animation = owner_.GetAnimation();
	if (animation.IsPlay())
	{
		isEnd_ = true;
	}
}

void ComponentLogicDropRock::Remove()
{
}

void ComponentLogicDropRock::AttackReset()
{
}

float ComponentLogicDropRock::SetRandomPosX(void)
{
	float ret = 0.0f;
	int min = 128 + ROCK_SIZE;
	int max = Application::SCREEN_SIZE_X - ROCK_SIZE - 128;

	ret = min + std::rand() % (max - min);
	return ret;
}
