#include "../../Object/Character/Player.h"
#include "ComponentAvilitySuperman.h"

ComponentAvilitySuperman::ComponentAvilitySuperman(Player& owner) :
	ComponentAvilityBase(owner)
{
	type_ = AvilityTypes::TYPE::SUPERMAN;
}

ComponentAvilitySuperman::~ComponentAvilitySuperman()
{	
}

void ComponentAvilitySuperman::Init()
{	
	parameter_.attackBoostRate_ += ADD_ATTACK_POWER_BOOST_RATE;
	parameter_.moveSpeedBoostRate_ += ADD_MOVE_SPEED_BOOST_RATE;
	parameter_.jumpPowMax_ += ADD_JUMP_POWER_MAX;
}

void ComponentAvilitySuperman::Remove()
{
	parameter_.attackBoostRate_ -= ADD_ATTACK_POWER_BOOST_RATE;
	parameter_.moveSpeedBoostRate_ -= ADD_MOVE_SPEED_BOOST_RATE;
	parameter_.jumpPowMax_ -= ADD_JUMP_POWER_MAX;
}
