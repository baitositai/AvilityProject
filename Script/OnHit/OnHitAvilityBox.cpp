#include "../Utility/UtilityCommon.h"
#include "../Object/Gimmick/AvilityBox.h"
#include "../Collider/ColliderArray.h"
#include "../Collider/ColliderBox.h"
#include "./OnHitAvilityBox.h"
#include "OnHitItem.h"
#include "../Parameter/Gimmick/ParameterAvilityBox.h"
#include "../Parameter/Character/ParameterCharacter.h"
#include "../Parameter/ParameterActor.h"

OnHitAvilityBox::OnHitAvilityBox(AvilityBox& owner) :
    OnHitBase(owner),
    owner_(owner)
{
    onHitMap_.emplace(CollisionTags::TAG::PLAYER, [this](const std::weak_ptr<ColliderBase>& opponentCollider)
        {
            return OnHitPlayer(opponentCollider);
        });
    onHitMap_.emplace(CollisionTags::TAG::ENEMY_CLONE, [this](const std::weak_ptr<ColliderBase>& opponentCollider)
        {
            return OnHitEnemy(opponentCollider);
        });
    onHitMap_.emplace(CollisionTags::TAG::STAGE, [this](const std::weak_ptr<ColliderBase>& opponentCollider)
        {
            return OnHitStage(opponentCollider);
        });
    onHitMap_.emplace(CollisionTags::TAG::AVILITY_BOX, [this](const std::weak_ptr<ColliderBase>& opponentCollider)
        {
            return OnHitBox(opponentCollider);
        });
}

OnHitAvilityBox::~OnHitAvilityBox()
{
}

void OnHitAvilityBox::HitWall(void)
{
    // 座標修正は PushResult 側で行うため、ここではフラグチェックのみ
    if (owner_.GetIsHitWall()) { moveAmount_.x = 0.0f; }
}

void OnHitAvilityBox::OnHitPlayer(const std::weak_ptr<ColliderBase>& opponentCollider)
{
    auto collider = std::dynamic_pointer_cast<ColliderBox>(opponentCollider.lock());
    if (!collider) return;

    const auto& opOwner = opponentCollider.lock()->GetOwner();
    ParameterActor& myParam = owner_.GetParameter();
    const ParameterActor& opParam = opOwner.GetParameter();

    // プレイヤーが動いてなければ処理しない
    if (Vector2F::IsSameVector2F(opParam.moveAmount_, Vector2F())) return;

    // お互いの距離・方向
    Vector2F diff = Vector2F::SubVector2F(opParam.pos_, myParam.pos_);
    int signX = UtilityCommon::GetSign(diff.x);
    int signY = UtilityCommon::GetSign(diff.y);

    // それぞれのめり込み量
    float overlapX = static_cast<float>(myParam.hitSize_.x / 2)
        + static_cast<float>(collider->GetBoxHalfSize().x) - fabsf(diff.x);
    float overlapY = static_cast<float>(myParam.hitSize_.y / 2)
        + static_cast<float>(collider->GetBoxHalfSize().y) - fabsf(diff.y);

    // めり込み量が両方正（衝突している）なら処理する
    if (overlapX > 0.0f && overlapY > 0.0f)
    {
        // プレイヤーに押し出されているフラグを立てる
        owner_.SetPlayerPush();
        myParam.direction_ = opParam.direction_;

        // 座標を直接変えず、HitInfoに溜める
        AvilityBox::HitInfo info;
        info.priority = 1; // プレイヤーからの押し出し
        info.overlapX = overlapX;
        info.overlapY = overlapY;
        info.signX = signX;
        info.signY = signY;
        info.moveAmount = opParam.moveAmount_; // プレイヤーの移動量を引き継ぐ
        info.selfPlayerPush = true;

        owner_.AddHitInfo(info);
    }
}

void OnHitAvilityBox::OnHitEnemy(const std::weak_ptr<ColliderBase>& opponentCollider)
{
}

void OnHitAvilityBox::OnHitStage(const std::weak_ptr<ColliderBase>& opponentCollider)
{
    // ステージ（壁・床）との衝突処理
    auto colliderArray = std::dynamic_pointer_cast<ColliderArray>(opponentCollider.lock());
    if (!colliderArray) return;

    // 判定結果を取得
    const ColliderArray::Result& result = colliderArray->GetResult();

    // ステージにめり込んでいないなら何もしない
    if (!result.hit) return;

    ParameterActor& myParam = owner_.GetParameter();

    // タイルの左右上下の「境界線の座標」を計算する
    float tileLeft   = static_cast<float>(result.hitChipIndex.x * result.chipSize.x);
    float tileRight  = tileLeft + static_cast<float>(result.chipSize.x);
    float tileTop    = static_cast<float>(result.hitChipIndex.y * result.chipSize.y);
    float tileBottom = tileTop + static_cast<float>(result.chipSize.y);

    // ボックスの左右上下の「境界線の座標」を取得
    float myLeft   = myParam.pos_.x - (static_cast<float>(myParam.hitSize_.x) / 2.0f);
    float myRight  = myParam.pos_.x + (static_cast<float>(myParam.hitSize_.x) / 2.0f);
    float myTop    = myParam.pos_.y - (static_cast<float>(myParam.hitSize_.y) / 2.0f);
    float myBottom = myParam.pos_.y + (static_cast<float>(myParam.hitSize_.y) / 2.0f);

    // 各方向の純粋なめり込み量を計算（重なっている部分の幅）
    float overlapLeft   = myRight - tileLeft;
    float overlapRight  = tileRight - myLeft;
    float overlapTop    = myBottom - tileTop;
    float overlapBottom = tileBottom - myTop;

    // 左右のめり込みの小さい方をX方向のめり込み量とする
    float minOverlapX = (overlapLeft < overlapRight) ? overlapLeft : overlapRight;
    // 上下のめり込みの小さい方をY方向のめり込み量とする
    float minOverlapY = (overlapTop < overlapBottom) ? overlapTop : overlapBottom;

    // 実際に登録するデータ
    AvilityBox::HitInfo info;
    info.priority = 0; // 壁・床による押し戻しは最優先（0）
    info.moveAmount = Vector2F(0.0f, 0.0f);
    info.selfPlayerPush = owner_.GetIsPlayerPush();

    if (minOverlapX < minOverlapY)
    {
        // 横方向からの衝突（壁）
        if (minOverlapX <= 0.0f) return; // ここで確実に安全弁をかける

        info.overlapX = minOverlapX;
        info.overlapY = 0.0f;
        info.signX = (overlapLeft < overlapRight) ? 1 : -1; 
        info.signY = 0;
    }
    else
    {
        // 縦方向からの衝突（床・天井）
        if (minOverlapY <= 0.0f) return; // ここで確実に安全弁をかける

        info.overlapX = 0.0f;
        info.overlapY = minOverlapY;
        info.signX = 0;
        info.signY = (overlapTop < overlapBottom) ? 1 : -1;
    }

    // 壁に当たったフラグを通知
    owner_.SetIsHitWall(true);
    owner_.AddHitInfo(info);
}

void OnHitAvilityBox::OnHitBox(const std::weak_ptr<ColliderBase>& opponentCollider)
{
    auto collider = std::dynamic_pointer_cast<ColliderBox>(opponentCollider.lock());
    if (!collider) return;

    const ActorBase& opOwnerBase = opponentCollider.lock()->GetOwner();
    const AvilityBox* opOwner = dynamic_cast<const AvilityBox*>(&opOwnerBase);
    if (!opOwner) return;

    ParameterAvilityBox& myParam = static_cast<ParameterAvilityBox&>(owner_.GetParameter());
    const ParameterActor& opParam = opOwner->GetParameter();

    Vector2F diff = Vector2F::SubVector2F(opParam.pos_, myParam.pos_);
    int signX = UtilityCommon::GetSign(diff.x);
    int signY = UtilityCommon::GetSign(diff.y);

    float overlapX = static_cast<float>(myParam.hitSize_.x / 2)
        + static_cast<float>(collider->GetBoxHalfSize().x) - fabsf(diff.x);
    float overlapY = static_cast<float>(myParam.hitSize_.y / 2)
        + static_cast<float>(collider->GetBoxHalfSize().y) - fabsf(diff.y);

    if (overlapX < overlapY)
    {
        // ここでも座標は変えず、HitInfoに情報を登録するだけ
        AvilityBox::HitInfo info;

        // 相手がプレイヤーに押されているなら優先度を高く、自分が押されているなら低く
        info.priority = opOwner->GetIsPlayerPush() ? 2 : 3;
        info.overlapX = overlapX;
        info.overlapY = overlapY;
        info.signX = signX;
        info.signY = signY;

        // 相手の移動量をベースにする
        info.moveAmount = opParam.moveAmount_;
        info.selfPlayerPush = owner_.GetIsPlayerPush();

        owner_.AddHitInfo(info);
    }
    else
    {
        // 縦方向（上に乗った時など）の処理
        AvilityBox::HitInfo info;
        info.priority = 4;
        info.overlapX = 0.0f;
        info.overlapY = overlapY;
        info.signX = 0;
        info.signY = signY;
        owner_.AddHitInfo(info);
    }
}