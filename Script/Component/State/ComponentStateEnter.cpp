#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Game/GameManager.h"
#include "../../Object/Common/Animation.h"
#include "../../Object/Character/CharacterBase.h"
#include "ComponentStateEnter.h"

ComponentStateEnter::ComponentStateEnter(CharacterBase& owner) :
	ComponentCharacterStateBase(owner),
	owner_(owner)
{
	animationTime_ = 0.0f;
	state_ = STATE::START;
	stateChangeMap_.emplace(STATE::START, std::bind(&ComponentStateEnter::ChangeStateStart, this));
	stateChangeMap_.emplace(STATE::WAIT, std::bind(&ComponentStateEnter::ChangeStateWait, this));
	stateChangeMap_.emplace(STATE::END, std::bind(&ComponentStateEnter::ChangeStateEnd, this));
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
	stateChangeMap_[state_]();
}

void ComponentStateEnter::ChangeStateStart()
{
	update_ = std::bind(&ComponentStateEnter::UpdateStart, this);
}

void ComponentStateEnter::ChangeStateWait()
{
	update_ = std::bind(&ComponentStateEnter::UpdateWait, this);	
	animationTime_ = 0.0f;
	owner_.GetAnimation().Play(Animation::TYPE::WALK);
}

void ComponentStateEnter::ChangeStateEnd()
{
	update_ = std::bind(&ComponentStateEnter::UpdateEnd, this);
	GameManager::GetInstance().ChangeState(GameManager::STATE::BOSS);
	owner_.ChangeState(CharacterBase::STATE::ALIVE);
}
