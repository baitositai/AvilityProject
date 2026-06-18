#include "../Parameter/ParameterActor.h"
#include "../Utility/UtilityCommon.h"
#include "../Component/ComponentBase.h"
#include "ComponentGravity.h"

ComponentGravity::ComponentGravity(ActorBase& owner) :
	ComponentBase(owner),
    parameter_(owner.GetParameter())
{
}

ComponentGravity::~ComponentGravity()
{
}

void ComponentGravity::Update()
{
    const float gravity = owner_.GetGravityPowerWithBoost();
    const ParameterActor::DIR dir = parameter_.gravityDir_;
    const Vector2F dirNor = parameter_.GetDown();

    // d—Í‚É‰‚¶‚Ä•ÏŠ·
    Vector2F moveAmount = UtilityCommon::ConvertLocalToWorldByGravity(parameter_.moveAmount_, dir);

    // d—Í‚ğ‰ÁZ
    moveAmount.x += dirNor.x * gravity;
    moveAmount.y += dirNor.y * gravity;

    // Ši”[
    parameter_.moveAmount_ = moveAmount;
}