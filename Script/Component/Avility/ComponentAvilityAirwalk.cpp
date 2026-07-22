#include "../../Object/Character/Player.h"
#include "../../Parameter/Character/Player/ParameterPlayer.h"
#include "ComponentAvilityAirwalk.h"

ComponentAvilityAirwalk::ComponentAvilityAirwalk(Player& owner) :
	ComponentAvilityBase(owner)
{
	type_ = AvilityTypes::TYPE::AIRWALK;
}

ComponentAvilityAirwalk::~ComponentAvilityAirwalk()
{
}

void ComponentAvilityAirwalk::Create()
{
	ComponentAvilityBase::Create();
	parameter_.jumpCountMax_ += ADD_JUMP_COUNT;
}

void ComponentAvilityAirwalk::Init()
{
}

void ComponentAvilityAirwalk::Remove()
{
	parameter_.jumpCountMax_ -= ADD_JUMP_COUNT;
}
