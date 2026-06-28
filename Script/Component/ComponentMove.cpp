#include "../../Manager/Game/CollisionManager.h"
#include "../../Collider/ColliderArray.h"
#include "../../Object/Common/Animation.h"
#include "ComponentMove.h"

ComponentMove::ComponentMove(ActorBase& owner) :
    ComponentBase(owner),
    owner_(owner),
    parameter_(owner_.GetParameter()),
    collisionManager_(CollisionManager::GetInstance())
{
    moveAmount_ = {};
    pos_ = {};
    defaultSize_ = {};
    nowSize_ = {};
    gravityDir_ = ParameterActor::DIR::MAX;
}

ComponentMove::~ComponentMove()
{
}

void ComponentMove::Update()
{
    moveAmount_ = parameter_.moveAmount_;

    // 移動がない場合は何もしない
    if (moveAmount_.x == 0.0f && moveAmount_.y == 0.0f)
    {
        return;
    }

	// パラメータの取得
    pos_ = parameter_.pos_;
    defaultSize_ = parameter_.hitSize_;
    gravityDir_ = parameter_.gravityDir_;

    // 重力方向に合わせたサイズ調整
    bool isVerticalGravity = (gravityDir_ == ParameterActor::DIR::UP || gravityDir_ == ParameterActor::DIR::DOWN);
    nowSize_.x = isVerticalGravity ? defaultSize_.x : defaultSize_.y;
    nowSize_.y = isVerticalGravity ? defaultSize_.y : defaultSize_.x;

    // 各軸の衝突判定
    ProcessCollision(true);  // X軸
    ProcessCollision(false); // Y軸

	// 座標と移動量の更新
    parameter_.pos_ = pos_;
    parameter_.moveAmount_ = moveAmount_;
}

void ComponentMove::ProcessCollision(bool isXAxis)
{
    float& moveVal = isXAxis ? moveAmount_.x : moveAmount_.y;
    if (moveVal == 0.0f)
    {
        return;
    }

    float& currentPos = isXAxis ? pos_.x : pos_.y;
    float sizeVal = isXAxis ? nowSize_.x : nowSize_.y;

    currentPos += moveVal;

    CollisionManager::CollisionCheckParam checkParameter;
    checkParameter.pos = pos_.ToVector2();
    checkParameter.size = nowSize_;
    checkParameter.isXAxis = isXAxis;
    checkParameter.stepMove = moveVal;

    CollisionManager:: CollisionResult result = collisionManager_.CheckStageCollision(checkParameter);

    if (result.isHit)
    {
        CheckGroundStatus(moveVal, isXAxis);

        float boundaryPos = (moveVal > 0.0f)
            ? static_cast<float>(result.chipIndex * result.chipSize)
            : static_cast<float>((result.chipIndex + 1) * result.chipSize);

        currentPos = (moveVal > 0.0f)
            ? boundaryPos - (sizeVal / 2.0f)
            : boundaryPos + (sizeVal / 2.0f);

        moveVal = 0.0f;
    }
}

void ComponentMove::CheckGroundStatus(float moveVal, bool isXAxis)
{
    bool isGround = false;
    if (isXAxis)
    {
        if ((moveVal > 0.0f && gravityDir_ == ParameterActor::DIR::RIGHT) ||
            (moveVal < 0.0f && gravityDir_ == ParameterActor::DIR::LEFT)) isGround = true;
    }
    else
    {
        if ((moveVal > 0.0f && gravityDir_ == ParameterActor::DIR::DOWN) ||
            (moveVal < 0.0f && gravityDir_ == ParameterActor::DIR::UP)) isGround = true;
    }

    if (isGround)
    {
        // 着地処理
        owner_.Landing();
    }
}