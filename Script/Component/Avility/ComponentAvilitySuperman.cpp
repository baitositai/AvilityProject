#include "../../Object/Character/Player.h"
#include "ComponentAvilitySuperman.h"

ComponentAvilitySuperman::ComponentAvilitySuperman(Player& owner) :
	ComponentAvilityBase(owner)
{
	type_ = AvilityTypes::TYPE::SUPERMAN;
	abilitySlot_ = ABILITY_SLOT::THIRD;
	owner_.AddAttackBoostRate(ADD_ATTACK_POWER_BOOST_RATE);
	owner_.AddMoveSpeedBoostRate(ADD_MOVE_SPEED_BOOST_RATE);
	owner_.AddJumpPowMax(ADD_JUMP_POWER_MAX);

}

ComponentAvilitySuperman::~ComponentAvilitySuperman()
{
}

void ComponentAvilitySuperman::Remove()
{
	owner_.AddAttackBoostRate(-ADD_ATTACK_POWER_BOOST_RATE);
	owner_.AddMoveSpeedBoostRate(-ADD_MOVE_SPEED_BOOST_RATE);	
	owner_.AddJumpPowMax(-ADD_JUMP_POWER_MAX);
}
