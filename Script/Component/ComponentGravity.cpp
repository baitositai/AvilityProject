#include "../Parameter/ParameterActor.h"
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

    // èdóÕÇâ¡éZ
    parameter_.moveAmount_.x += dirNor.x * gravity;
    parameter_.moveAmount_.y += dirNor.y * gravity;
}