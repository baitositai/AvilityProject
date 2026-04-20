#include "../Object/Character/Player.h"
#include "../Collider/ColliderArray.h"
#include "OnHitPlayer.h"

OnHitPlayer::OnHitPlayer(Player& owner) :
    OnHitBase(owner),
    owner_(owner)
{
    onHitMap_.emplace(CollisionTags::TAG::STAGE , [this](const std::weak_ptr<ColliderBase>& opponentCollider)
        {
            return OnHitStage(opponentCollider);
        });
}

OnHitPlayer::~OnHitPlayer()
{
}

void OnHitPlayer::OnHitStage(const std::weak_ptr<ColliderBase>& opponentCollider)
{
    // 配列用コライダーへ変換
    auto collider = std::dynamic_pointer_cast<ColliderArray>(opponentCollider.lock());

    // 衝突結果からヒットしたインデックスを取得
    const Vector2 hitIndex = collider->GetResult().hitIndex;

    // 移動量取得
    const Vector2F moveAmount = owner_.GetParameter()->moveAmount;

    // プレイヤー座標取得
    Vector2F pos = owner_.GetParameter()->pos;
    
    // 右へ移動中の場合
    if (moveAmount.x > 0) 
    {
        // 右壁へ
        pos.x = hitIndex.x * collider->GetChipSize().x - owner_.GetHitBoxSize().x / 2;
    }
    // 左へ移動中の場合
    else if (moveAmount.x < 0) // 左へ移動中なら左壁
    {
        // 左壁へ
        pos.x = (hitIndex.x + 1) * collider->GetChipSize().x;
    }
    // 落下中の場合
    if (moveAmount.y > 0)
    {
        // 地面へ
        pos.y = hitIndex.y * collider->GetChipSize().y - owner_.GetHitBoxSize().y / 2;
        //isOnGround_ = true; // 着地フラグを立てる
    }
    // 上へ移動中の場合
    else if (moveAmount.y < 0)
    {
        // 天井へ
        pos.y = (hitIndex.y + 1) * collider->GetChipSize().y;
    }

    // 座標の設定
    owner_.SetPosition(pos);

    // 移動量を初期化
    owner_.SetMoveAmount(Vector2F(0.0f, 0.0f));

    // 判定結果を初期化
    collider->SetResult(ColliderArray::Result());
}
