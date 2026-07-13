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

	//待機アニメーション
	owner_.GetAnimation().Play(Animation::TYPE::ATTACK_2, false);
	int createRockNum = ROCK_CREATE_NUM_MIN;
	const int playerNum = playerManager_.GetPlayerNum();
	std::vector<Vector2F> playersPos = playerManager_.GetPlayersPos();

	// 攻撃のコライダー設定
	attackCollider_->SetIsActive(true);

	for (int i = 0; i < createRockNum; i++)
	{
		////岩生成
		//GimmickManager::CreateParameter createParameter = {};
		//createParameter.type = GimmickTypes::TYPE::DROP_ROCK;
		//createParameter.pos = Vector2F::AddVector2F(owner_.GetParameter().pos_);
		//createParameter.attackPower = ATTACK_POINT;
		//gimmickManager_.Create(createParameter);
	}
}

void ComponentLogicGroundRock::Update()
{
}

void ComponentLogicGroundRock::Remove()
{
}

void ComponentLogicGroundRock::AttackReset()
{
}
