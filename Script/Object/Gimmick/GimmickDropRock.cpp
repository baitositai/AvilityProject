#include "../Manager/Common/SceneManager.h"
#include "../Manager/Game/CollisionManager.h"
#include "../Manager/Common/SpriteEffectManager.h"
#include "../Manager/Common/Camera.h"
#include "../../Parameter/Gimmick/ParameterGimmick.h"
#include "../../Parameter/Effect/ParameterEffect.h"
#include "../../OnHit/OnHitDropRock.h"
#include "../Collider/ColliderCircle.h"
#include "GimmickDropRock.h"

GimmickDropRock::GimmickDropRock(std::unique_ptr<ParameterGimmick> parameter):
	GimmickBase(std::move(parameter)),
	state_(STATE::NONE),
	parameterDropRock_(),
	hitRadius_(ROCK_SIZE),
	isDead_(false)
{
	// パラメータ情報
	parameterDropRock_ = dynamic_cast<ParameterGimmick*>(GetParameterGimmickPtr());
	assert(parameterDropRock_ != nullptr);
}

GimmickDropRock::~GimmickDropRock()
{
}

void GimmickDropRock::Init()
{
	//ロックサイズのヒットサイズ設定
	parameterDropRock_->hitSize_ = Vector2(ROCK_SIZE, ROCK_SIZE);

	// コライダー
	collider_ = std::make_shared<ColliderCircle>(*this, CollisionTags::TAG::DROP_ROCK, parameterDropRock_->pos_, hitRadius_);

	// 衝突後処理
	onHit_ = std::make_unique<OnHitDropRock>(*this);

	// 初期化
	GimmickBase::Init();

	isDead_ = false;
	waitCnt_ = 0.0f;

	update_ = std::bind(&GimmickDropRock::UpdateWait, this);
}

void GimmickDropRock::Update()
{
	update_();

	// 基底クラスの処理
	ActorBase::Update();
}

void GimmickDropRock::UpdateWait(void)
{
	if (waitCnt_ > WAIT_TIME)
	{
		update_ = std::bind(&GimmickDropRock::UpdateDrop, this);
	}
	// コンポーネント無効
	SetComponentActive("gravity", false);
	SetComponentActive("move", false);
	waitCnt_ += scnMng_.GetDeltaTime();
}

void GimmickDropRock::UpdateDrop(void)
{
	CollisionManager::CollisionCheckParam checkParameter;
	checkParameter.pos = parameterDropRock_->pos_.ToVector2();
	checkParameter.size = parameterDropRock_->hitSize_;
	checkParameter.isXAxis = false;
	checkParameter.stepMove = parameterDropRock_->gravityPower_;
	CollisionManager::CollisionResult result = CollisionManager::GetInstance().CheckStageCollision(checkParameter);
	if (result.isHit)
	{
		//ステージと当たったら消す
		collider_->Delete();
		isDead_ = true;
		isDelete_ = true;
		scnMng_.GetCamera().SetCameraShake(CAMERA_SHAKE_TIME, CAMERA_SHAKE_POWER);

		//エフェクト再生
		SpriteEffectManager::CreateParameter parameter = {};
		parameter.pos = parameterDropRock_->pos_;
		parameter.scale = parameterDropRock_->scale_;
		parameter.resourceKey = "rockLanding";
		effectMng_.Create(parameter);
	}
	// コンポーネント有効
	SetComponentActive("gravity", true);
	SetComponentActive("move", true);
}

void GimmickDropRock::UpdateGroundRock()
{
}

void GimmickDropRock::PlayEffect(void)
{
}

void GimmickDropRock::CheckGroundStatus(float moveVal, bool isXAxis)
{
	bool isGround = false;
	if (isXAxis)
	{
		if ((moveVal > 0.0f && parameterDropRock_->gravityDir_ == ParameterActor::DIR::RIGHT) ||
			(moveVal < 0.0f && parameterDropRock_->gravityDir_ == ParameterActor::DIR::LEFT)) isGround = true;
	}
	else
	{
		if ((moveVal > 0.0f && parameterDropRock_->gravityDir_ == ParameterActor::DIR::DOWN) ||
			(moveVal < 0.0f && parameterDropRock_->gravityDir_ == ParameterActor::DIR::UP)) isGround = true;
	}

	if (isGround) parameterDropRock_->isGround_ = true;
}