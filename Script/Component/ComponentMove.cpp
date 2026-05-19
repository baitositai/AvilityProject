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
    if (moveVal == 0.0f) return;

    float& currentPos = isXAxis ? pos_.x : pos_.y;
    float sizeVal = isXAxis ? nowSize_.x : nowSize_.y;
    float otherSizeVal = isXAxis ? nowSize_.y : nowSize_.x; // 判定する「面」の幅

    // 座標更新
    currentPos += moveVal;

    // 四隅・多点判定の追加
    bool isHit = false;
    ColliderArray::Result finalResult;

    // 判定点のリスト（進行方向の面の、左端・中央・右端の3点）
    // 0.5fを調整することで、角の判定を少し内側に寄せる（あそびを作る）ことも可能
    float margin = 0.45f;
    float offsets[] = { -margin, 0.0f, margin };

    for (float offset : offsets)
    {
        Vector2 checkPos = pos_.ToVector2();
        if (isXAxis)
        {
            // X移動時：進行方向の「縦の面」を3点チェック
            checkPos.x += (moveVal > 0.0f) ? sizeVal / 2.0f : -sizeVal / 2.0f;
            checkPos.y += otherSizeVal * offset;
        }
        else
        {
            // Y移動時：進行方向の「横の面」を3点チェック
            checkPos.y += (moveVal > 0.0f) ? sizeVal / 2.0f : -sizeVal / 2.0f;
            checkPos.x += otherSizeVal * offset;
        }

        auto result = collisionManager_.IsHitStage(checkPos);
        if (result.hit)
        {
            isHit = true;
            finalResult = result;
            break; // 1点でも当たっていれば衝突とみなす
        }
    }

    if (isHit)
    {
        CheckGroundStatus(moveVal, isXAxis);

        float chipSize = isXAxis ? finalResult.chipSize.x : finalResult.chipSize.y;
        int chipIndex = isXAxis ? finalResult.hitChipIndex.x : finalResult.hitChipIndex.y;

        float boundaryPos = (moveVal > 0.0f)
            ? static_cast<float>(chipIndex * chipSize)
            : static_cast<float>((chipIndex + 1) * chipSize);

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