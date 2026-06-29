#include "../../Utility/UtilityCommon.h"
#include "../../Manager/Game/CollisionManager.h"
#include "../../Collider/ColliderBox.h"
#include "../../OnHit/OnHitBamboo.h"
#include "GimmickBamboo.h"

GimmickBamboo::GimmickBamboo(std::unique_ptr<ParameterGimmickBamboo> parameter) :
	GimmickBase(std::move(parameter))
{
	// パラメータ情報
	parameterBamboo_ = dynamic_cast<ParameterGimmickBamboo*>(GetParameterGimmickPtr());
	assert(parameterBamboo_ != nullptr);

	reflectCount_ = 0;
}

GimmickBamboo::~GimmickBamboo()
{
}

void GimmickBamboo::Init()
{
	// コライダー
	collider_ = std::make_shared<ColliderBox>(*this, CollisionTags::TAG::BAMBOO, parameterBamboo_->pos_, parameterBamboo_->hitSize_, parameterBamboo_->angle_);

	// 衝突後処理
	onHit_ = std::make_unique<OnHitBamboo>(*this);

	// 初期化
	ActorBase::Init();
}

void GimmickBamboo::Update()
{
	// 移動処理
	parameterBamboo_->moveAmount_ = Vector2F::MulVector2FFloat(parameterBamboo_->moveDir_, parameterBamboo_->moveSpeed_);

	// 角度を決める（通常の2D座標系における移動方向の角度を出す）
	// ※DXライブラリのY軸は下がプラスなので、通常の atan2f(y, x) で時計回りの角度になります
	float targetAngle = std::atan2f(parameterBamboo_->moveDir_.y, parameterBamboo_->moveDir_.x);

	parameterBamboo_->angle_ = targetAngle - (DX_PI_F / 2.0f);

	// 移動方向に応じて反対にする
	parameterBamboo_->direction_ = parameterBamboo_->moveDir_.x > 0 ? false : true;

	// 各軸の衝突判定
	ProcessCollision(true);
	ProcessCollision(false);

	// 基底クラスの処理
	ActorBase::Update();
}

void GimmickBamboo::ProcessCollision(bool isXAxis)
{
	float& moveVal = isXAxis ? parameterBamboo_->moveAmount_.x : parameterBamboo_->moveAmount_.y;
	if (moveVal == 0.0f)
	{
		return;
	}

	float& currentPos = isXAxis ? parameterBamboo_->pos_.x : parameterBamboo_->pos_.y;

	float move = moveVal;
	float maxStep = 8.0f;
	int step = static_cast<int>(std::ceil(std::abs(move) / maxStep));
	if (step <= 0)
	{
		step = 1;
	}
	float stepMove = move / step;

	for (int i = 0; i < step; i++)
	{
		currentPos += stepMove;

		CollisionManager::CollisionCheckParam checkParameter;
		checkParameter.pos = parameterBamboo_->pos_.ToVector2();
		checkParameter.size = parameterBamboo_->hitSize_;
		checkParameter.isXAxis = isXAxis;
		checkParameter.stepMove = stepMove;

		CollisionManager::CollisionResult result = CollisionManager::GetInstance().CheckStageCollision(checkParameter);

		if (result.isHit)
		{
			// 1個戻す
			currentPos -= stepMove;

			CheckGroundStatus(stepMove, isXAxis);

			// 反射ベクトル計算（共通化した法線を使用）
			Vector2F reflectDir = UtilityCommon::Reflect(parameterBamboo_->moveDir_, result.normal);
			parameterBamboo_->moveDir_ = reflectDir;

			// 反射回数追加
			reflectCount_++;

			// 一定回数反射したら
			if (reflectCount_ > parameterBamboo_->reflectCountMax_)
			{
				Delete();
				return;
			}

			moveVal = 0.0f;
		}
		else
		{
		}
	}
}
void GimmickBamboo::CheckGroundStatus(float moveVal, bool isXAxis)
{
	bool isGround = false;
	if (isXAxis)
	{
		if ((moveVal > 0.0f && parameterBamboo_->gravityDir_ == ParameterActor::DIR::RIGHT) ||
			(moveVal < 0.0f && parameterBamboo_->gravityDir_ == ParameterActor::DIR::LEFT)) isGround = true;
	}
	else
	{
		if ((moveVal > 0.0f && parameterBamboo_->gravityDir_ == ParameterActor::DIR::DOWN) ||
			(moveVal < 0.0f && parameterBamboo_->gravityDir_ == ParameterActor::DIR::UP)) isGround = true;
	}

	if (isGround) parameterBamboo_->isGround_ = true;
}