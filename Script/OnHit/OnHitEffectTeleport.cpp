#include "../../Object/Effect/EffectBase.h"
#include "OnHitEffectTeleport.h"

OnHitEffectTeleport::OnHitEffectTeleport(EffectBase& owner) :
	OnHitEffect(owner),
	owner_(owner)
{

}

OnHitEffectTeleport::~OnHitEffectTeleport()
{
}
