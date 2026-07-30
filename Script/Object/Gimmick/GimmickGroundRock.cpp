#include "../Utility/UtilityCommon.h"
#include "../Manager/Common/SceneManager.h"
#include "../Manager/Common/SoundManager.h"
#include "../Manager/Common/Camera.h"
#include "../Manager/Common/SpriteEffectManager.h"
#include "../Manager/Game/CollisionManager.h"
#include "../../Parameter/Gimmick/ParameterGimmickGroundRock.h"
#include "../../OnHit/OnHitGroundRock.h"
#include "../Collider/ColliderCircle.h"
#include "GimmickGroundRock.h"

GimmickGroundRock::GimmickGroundRock(std::unique_ptr<ParameterGimmickGroundRock> parameter):
	GimmickBase(std::move(parameter)),
	hitRadius_(ROCK_SIZE),
	jumpPow_(),
	velocity_()
{
	// パラメータ情報
	parameterGroundRock_ = dynamic_cast<ParameterGimmickGroundRock*>(GetParameterGimmickPtr());
	assert(parameterGroundRock_ != nullptr);
}

GimmickGroundRock::~GimmickGroundRock()
{
}

void GimmickGroundRock::Init()
{
	parameterGroundRock_->hitSize_ = Vector2(ROCK_SIZE, ROCK_SIZE);
	// コライダー
	collider_ = std::make_shared<ColliderCircle>(*this, CollisionTags::TAG::GROUND_ROCK, parameterGroundRock_->pos_, hitRadius_);
	collMng_.Add(collider_);
	parameterGroundRock_->angle_ = UtilityCommon::Deg2RadF(std::rand() % static_cast<int>(ANGLE_MAX));
	// 衝突後処理
	onHit_ = std::make_unique<OnHitGroundRock>(*this);
	//ジャンプ力セット
	jumpPow_ = 30.0f;
	velocity_ = 20.0f;
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
		scnMng_.GetCamera().SetCameraShake(CAMERA_SHAKE_TIME, CAMERA_SHAKE_POWER);

		//エフェクト再生
		SpriteEffectManager::CreateParameter parameter = {};
		parameter.pos = parameterGroundRock_->pos_;
		parameter.scale = parameterGroundRock_->scale_;
		parameter.resourceKey = "rockBreak";
		parameter.animationSpeed = 0.2f;
		effectMng_.Create(parameter);

		sndMng_.PlaySe(SoundType::SE::ROCK_DESTROY);

		return;
	}
	// コンポーネント有効
	SetComponentActive("gravity", true);
	SetComponentActive("move", true);
	velocity_ -= parameterGroundRock_->gravityPower_;
	jumpPow_ = velocity_;
	//放物線上に移動
	parameterGroundRock_->pos_.y -= jumpPow_;
	parameterGroundRock_->pos_.x -= parameterGroundRock_->horizonSpd_;

	//角度を回転
	parameterGroundRock_->angle_ += UtilityCommon::Deg2RadF(ANGLE_SPD);

	// 基底クラスの処理
	ActorBase::Update();
}
