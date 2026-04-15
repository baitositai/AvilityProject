#include "../Component/ComponentBase.h"
#include "CharacterBase.h"

CharacterBase::CharacterBase(Parameter* parameter, const std::vector<std::string> componentNameList):
	ActorBase(parameter, componentNameList),
	characterParameterPtr_(parameter)
{
	// ó‘Ô‘JˆÚˆ—‚Ì“o˜^
	stateChangeMap_.emplace(STATE::ALIVE, std::bind(&CharacterBase::ChangeStateAlive, this));
	stateChangeMap_.emplace(STATE::DEAD, std::bind(&CharacterBase::ChangeStateDead, this));
	stateChangeMap_.emplace(STATE::RESPAWN, std::bind(&CharacterBase::ChangeStateRespawn, this));
}

CharacterBase::~CharacterBase()
{
	componentMap_.clear();
}

void CharacterBase::Init()
{
	// ‰Šúó‘Ô‚ðÝ’è
	ChangeState(STATE::ALIVE);
}

void CharacterBase::Update()
{
	updateStateFunction_();
}

void CharacterBase::ChangeState(const STATE state)
{
	state_ = state;
	
	// ó‘Ô‘JˆÚˆ—‚ÌŒÄ‚Ño‚µ
	auto it = stateChangeMap_.find(state_);
	if (it != stateChangeMap_.end())
	{
		it->second();
	}
}

void CharacterBase::ChangeStateRespawn()
{
	updateStateFunction_ = std::bind(&CharacterBase::UpdateStateRespawn, this);
}

void CharacterBase::ChangeStateAlive()
{
	updateStateFunction_ = std::bind(&CharacterBase::UpdateStateAlive, this);
}

void CharacterBase::ChangeStateDead()
{
	updateStateFunction_ = std::bind(&CharacterBase::UpdateStateDead, this);
}

void CharacterBase::UpdateStateRespawn()
{
}

void CharacterBase::UpdateStateAlive()
{
}

void CharacterBase::UpdateStateDead()
{
}