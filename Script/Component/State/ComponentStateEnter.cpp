#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Game/GameManager.h"
#include "../../Manager/Game/EnemyManager.h"
#include "../../Manager/Game/PlayerManager.h"
#include "../../Object/Common/Animation.h"
#include "../../Object/Character/CharacterBase.h"
#include "ComponentStateEnter.h"

ComponentStateEnter::ComponentStateEnter(CharacterBase& owner) :
	ComponentCharacterStateBase(owner),
	owner_(owner)
{
	animationTime_ = 0.0f;
	state_ = STATE::START;
	changeStateMap_.emplace(STATE::START, std::bind(&ComponentStateEnter::ChangeStateStart, this));
	changeStateMap_.emplace(STATE::WAIT, std::bind(&ComponentStateEnter::ChangeStateWait, this));
	changeStateMap_.emplace(STATE::END, std::bind(&ComponentStateEnter::ChangeStateEnd, this));
	ChangeState(STATE::START);
}

ComponentStateEnter::~ComponentStateEnter()
{
}

void ComponentStateEnter::Init()
{
	ChangeState(STATE::START);
}

void ComponentStateEnter::Update()
{
	update_();
}

void ComponentStateEnter::UpdateStart()
{
	ChangeState(STATE::WAIT);
}

void ComponentStateEnter::UpdateWait()
{
	animationTime_ += SceneManager::GetInstance().GetDeltaTime();
	if (animationTime_ > ANIMATION_TIME)
	{
		ChangeState(STATE::END);
	}
}

void ComponentStateEnter::UpdateEnd()
{
	
}

void ComponentStateEnter::ChangeState(const STATE state)
{
	state_ = state;
	changeStateMap_[state_]();
}

void ComponentStateEnter::ChangeStateStart()
{
	update_ = std::bind(&ComponentStateEnter::UpdateStart, this);
}

void ComponentStateEnter::ChangeStateWait()
{
	update_ = std::bind(&ComponentStateEnter::UpdateWait, this);	
	animationTime_ = 0.0f;
	owner_.SetColliderActive(false);
	owner_.GetAnimation().Play(Animation::TYPE::WALK);	
	EnemyManager::GetInstance().SetIsStop(true);
	PlayerManager::GetInstance().SetAllIsActive(false);
	owner_.SetIsActive(true);
}

void ComponentStateEnter::ChangeStateEnd()
{
	update_ = std::bind(&ComponentStateEnter::UpdateEnd, this);
	SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::BOSS);
	owner_.ChangeState(CharacterBase::STATE::ALIVE);
}
