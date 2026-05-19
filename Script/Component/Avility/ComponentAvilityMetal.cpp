#include "../../Object/Character/Player.h"
#include "ComponentAvilityMetal.h"

ComponentAvilityMetal::ComponentAvilityMetal(Player& owner) :
	ComponentAvilityBase(owner)
{
	type_ = AvilityTypes::TYPE::METAL;
	abilitySlot_ = ABILITY_SLOT::THIRD;
	parameter_.damageRate_ -= ADD_DAMAGE_RATE;
	parameter_.gravityBoostRate_ += GRAVITY_BOOST_RATE;
}

ComponentAvilityMetal::~ComponentAvilityMetal()
{
}

void ComponentAvilityMetal::Remove()
{
	parameter_.damageRate_ += ADD_DAMAGE_RATE;
	parameter_.gravityBoostRate_ -= GRAVITY_BOOST_RATE;
}