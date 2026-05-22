#include "../../Object/Character/Player.h"
#include "ComponentAvilityGiant.h"

ComponentAvilityGiant::ComponentAvilityGiant(Player& owner) :
	ComponentAvilityBase(owner)
{
	// éÌóﬁÇÃê›íË
	abilitySlot_ = ABILITY_SLOT::THIRD;
	type_ = AvilityTypes::TYPE::GIANT;

	// ëÂÇ´Ç≥ÇïœçX
	parameter_.scale_ = SCALE;
	parameter_.hitRadius_ *= SCALE;
	parameter_.hitSize_ = Vector2F::MulVector2FFloat(parameter_.hitSize_.ToVector2F(), SCALE).ToVector2();

	// ínñ Ç…ñÑÇ‹ÇÁÇ»Ç¢ÇÊÇ§Ç…à íuÇÇ∏ÇÁÇ∑
	float sizeY = static_cast<float>(parameter_.hitSize_.y);
	float offset = (sizeY * SCALE - sizeY) / 2.0f;
	parameter_.pos_ = Vector2F::AddVector2F(parameter_.pos_, Vector2F::MulVector2FFloat(parameter_.GetUp(), offset));
}

ComponentAvilityGiant::~ComponentAvilityGiant()
{
}

void ComponentAvilityGiant::Update()
{

}

void ComponentAvilityGiant::Remove()
{
	parameter_.scale_ = 1.0f;
	parameter_.hitRadius_ /= SCALE;
	parameter_.hitSize_ = Vector2F::DivVector2F(parameter_.hitSize_.ToVector2F(), Vector2F(SCALE, SCALE)).ToVector2();
}