#include <DxLib.h>
#include "../Manager/Common/SceneManager.h"
#include "../Manager/Common/Camera.h"
#include "../Utility/UtilityCommon.h"
#include "../Object/ActorBase.h"
#include "ColliderCircle.h"

ColliderCircle::ColliderCircle(ActorBase& owner, const CollisionTags::TAG tag, Vector2F& followPos, float& radius) :
	ColliderBase(owner, tag, followPos),
	radius_(radius)
{
	type_ = ColliderType::TYPE::CIRCLE;
}

ColliderCircle::~ColliderCircle()
{
}

std::shared_ptr<ColliderBase> ColliderCircle::Clone() const
{
	return std::make_shared<ColliderCircle>(*this);
}

void ColliderCircle::DebugDraw()
{
	if (!isActive_ || !owner_.IsActive()) return;
	Vector2F cameraPos = mainCamera.GetPos();
	Vector2 pos = Vector2::AddVector2(followPos_.ToVector2(), cameraPos.ToVector2());
	DrawCircle(pos.x, pos.y, radius_,  UtilityCommon::YELLOW, false , 1);
}
