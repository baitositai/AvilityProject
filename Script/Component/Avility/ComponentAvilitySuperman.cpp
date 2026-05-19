#include "../../Object/Character/Player.h"
#include "ComponentAvilitySuperman.h"

ComponentAvilitySuperman::ComponentAvilitySuperman(Player& owner) :
	ComponentAvilityBase(owner)
{
	type_ = AvilityTypes::TYPE::SUPERMAN;
	abilitySlot_ = ABILITY_SLOT::THIRD;
	parameter_.attackBoostRate_ += ADD_ATTACK_POWER_BOOST_RATE;
	parameter_.moveSpeedBoostRate_ += ADD_MOVE_SPEED_BOOST_RATE;
	parameter_.jumpPowMax_ += ADD_JUMP_POWER_MAX;

}

ComponentAvilitySuperman::~ComponentAvilitySuperman()
{
}

void ComponentAvilitySuperman::Remove()
{
	parameter_.attackBoostRate_ -= ADD_ATTACK_POWER_BOOST_RATE;
	parameter_.moveSpeedBoostRate_ -= ADD_MOVE_SPEED_BOOST_RATE;
	parameter_.jumpPowMax_ -= ADD_JUMP_POWER_MAX;
}
