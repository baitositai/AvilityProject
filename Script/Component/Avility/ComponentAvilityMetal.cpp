#include "../../Object/Character/Player.h"
#include "ComponentAvilityMetal.h"

ComponentAvilityMetal::ComponentAvilityMetal(Player& owner) :
	ComponentAvilityBase(owner)
{
	type_ = AvilityTypes::TYPE::METAL;
	abilitySlot_ = ABILITY_SLOT::THIRD;
	owner_.AddDamageRate(-ADD_DAMAGE_RATE);
	owner_.AddGravityBoostRate(GRAVITY_BOOST_RATE);
}

ComponentAvilityMetal::~ComponentAvilityMetal()
{
}

void ComponentAvilityMetal::Remove()
{
	owner_.AddDamageRate(ADD_DAMAGE_RATE);
	owner_.AddGravityBoostRate(-GRAVITY_BOOST_RATE);
}