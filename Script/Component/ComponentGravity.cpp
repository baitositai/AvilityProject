#include "../Component/ComponentBase.h"
#include "ComponentGravity.h"

ComponentGravity::ComponentGravity(ActorBase& owner) :
	ComponentBase(&owner)
{
}

ComponentGravity::~ComponentGravity()
{
}

void ComponentGravity::Update()
{
	// d—Í‚ðŽæ“¾
	const float gravity = owner_->GetParameter()->gravityPower;

	// d—Í•ûŒü‚ðŽæ“¾
	const Vector2F dir = GRAVITY_DIR_MAP.at(owner_->GetParameter()->gravityDir);

	// ˆÚ“®—Ê‚ÌŽæ“¾
	Vector2F moveAmount = owner_->GetParameter()->moveAmount;

	// d—Í•ûŒü‚É—Ž‚Æ‚·
	moveAmount = Vector2F::AddVector2F(moveAmount, Vector2F::MulVector2F(dir, Vector2F{ gravity, gravity }));

	// ˆÚ“®—Ê‚ðŠi”[
	owner_->SetMoveAmount(moveAmount);
}
