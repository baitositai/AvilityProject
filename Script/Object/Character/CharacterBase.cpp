#include <DxLib.h>
#include "../Utility/UtilityCommon.h"
#include "../Component/ComponentBase.h"
#include "../Collider/ColliderBase.h"
#include "CharacterBase.h"

CharacterBase::CharacterBase(Parameter* parameter, const std::vector<std::string> componentNameList):
	ActorBase(parameter, componentNameList),
	characterParameterPtr_(parameter)
{
	state_ = STATE::MAX;

	// ó‘Ô‘JˆÚˆ—‚Ì“o˜^
	stateChangeMap_.emplace(STATE::ALIVE, std::bind(&CharacterBase::ChangeStateAlive, this));
	stateChangeMap_.emplace(STATE::DEAD, std::bind(&CharacterBase::ChangeStateDead, this));
	stateChangeMap_.emplace(STATE::RESPAWN, std::bind(&CharacterBase::ChangeStateRespawn, this));
}

CharacterBase::~CharacterBase()
{
}

void CharacterBase::Init()
{
	ActorBase::Init();

	// ‰Šúó‘Ô‚ðÝ’è
	ChangeState(STATE::ALIVE);
}

void CharacterBase::Update()
{
	updateStateFunction_();
}

void CharacterBase::DebugDraw()
{
	if (collider_ == nullptr) return;
	collider_->DebugDraw();
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
	ActorBase::Update();
}

void CharacterBase::UpdateStateDead()
{
}