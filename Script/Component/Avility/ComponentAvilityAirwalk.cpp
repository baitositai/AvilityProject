#include "../../Object/Character/Player.h"
#include "ComponentAvilityAirwalk.h"

ComponentAvilityAirwalk::ComponentAvilityAirwalk(Player& owner) :
	ComponentAvilityBase(owner)
{
	abilitySlot_ = ABILITY_SLOT::SECOND;
	type_ = AvilityTypes::TYPE::AIRWALK;
}

ComponentAvilityAirwalk::~ComponentAvilityAirwalk()
{
}

void ComponentAvilityAirwalk::Update()
{
	if (owner_.GetJumpCount() < 1)
	{
		owner_.AddJumpCount(1);
	}
}
