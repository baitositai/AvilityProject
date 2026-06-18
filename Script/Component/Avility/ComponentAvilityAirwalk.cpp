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
}

void ComponentAvilityAirwalk::Init()
{
}

void ComponentAvilityAirwalk::Update()
{
	if (parameter_.jumpCount_ < 1)
	{
		parameter_.jumpCount_++;
	}
}