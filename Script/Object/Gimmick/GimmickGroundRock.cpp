#include "../Manager/Common/SceneManager.h"
#include "../Manager/Game/CollisionManager.h"
#include "../../Parameter/Gimmick/ParameterGimmick.h"
#include "../../OnHit/OnHitGroundRock.h"
#include "../Collider/ColliderCircle.h"
#include "GimmickGroundRock.h"

GimmickGroundRock::GimmickGroundRock(std::unique_ptr<ParameterGimmick> parameter):
	GimmickBase(std::move(parameter))
{
}

GimmickGroundRock::~GimmickGroundRock()
{
}

void GimmickGroundRock::Init()
{
	parameterGroundRock_->hitSize_ = Vector2(ROCK_SIZE, ROCK_SIZE);

	// コライダー
	collider_ = std::make_shared<ColliderCircle>(*this, CollisionTags::TAG::DROP_ROCK, parameterGroundRock_->pos_, hitRadius_);

	// 衝突後処理
	onHit_ = std::make_unique<OnHitGroundRock>(*this);

	// 初期化
	GimmickBase::Init();
}

void GimmickGroundRock::Update()
{
	CollisionManager::CollisionCheckParam checkParameter;
	checkParameter.pos = parameterGroundRock_->pos_.ToVector2();
	checkParameter.size = parameterGroundRock_->hitSize_;
	checkParameter.isXAxis = false;
	checkParameter.stepMove = parameterGroundRock_->gravityPower_;
	CollisionManager::CollisionResult result = CollisionManager::GetInstance().CheckStageCollision(checkParameter);

	if (result.isHit)
	{
		//ステージと当たったら消す
		collider_->Delete();
		isDelete_ = true;
	}
	// コンポーネント有効
	SetComponentActive("gravity", true);
	SetComponentActive("move", true);
}
