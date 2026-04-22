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
    onHitMap_.emplace(CollisionTags::TAG::AVILITY_BOX, [this](const std::weak_ptr<ColliderBase>& opponentCollider)
        {
            return OnHitAvilityBox(opponentCollider);
        });
}

OnHitPlayer::~OnHitPlayer()
{
}

void OnHitPlayer::OnHitStage(const std::weak_ptr<ColliderBase>& opponentCollider)
{
    auto collider = std::dynamic_pointer_cast<ColliderArray>(opponentCollider.lock());
    if (!collider) return;              // コライダーが空の場合終了

    // 当たったすべてのタイルインデックスを取得
    const auto& indexes = collider->GetResult().indexes;
    if (indexes.empty()) return;       // インデックスリストが空の場合終了

    Vector2F pos = owner_.GetParameter()->pos;          // 座標取得
    Vector2 boxSize = owner_.GetHitBoxSize();           // ボックスサイズ          
    Vector2 chipSize = collider->GetChipSize();         // チップサイズ

    for (const Vector2& index : indexes)
    {
        // 移動量取得
        Vector2F moveAmount = owner_.GetParameter()->moveAmount;

        // 移動量が0の場合
        if (moveAmount.x == 0.0f && moveAmount.y == 0.0f)
        {
            // 終了
            break;
        }

        // タイルの四隅
        float tLeft = index.x * chipSize.x;
        float tRight = tLeft + chipSize.x;
        float tTop = index.y * chipSize.y;
        float tBottom = tTop + chipSize.y;

        // プレイヤーの四端
        float pLeft = pos.x - boxSize.x / 2.0f;
        float pRight = pos.x + boxSize.x / 2.0f;
        float pTop = pos.y - boxSize.y / 2.0f;
        float pBottom = pos.y + boxSize.y / 2.0f;

        // どのくらいめり込み具合
        float overL = pRight - tLeft;
        float overR = tRight - pLeft;
        float overT = pBottom - tTop;
        float overB = tBottom - pTop;

        if (overL > 0 && overR > 0 && overT > 0 && overB > 0)
        {
            float minOverlap = 10000.0f;
            ActorBase::DIR dir = ActorBase::DIR::MAX;

            // 右に移動中の場合
            if (moveAmount.x > 0 && overL < minOverlap) 
            { 
                // 左へ押し戻す判定を有効にする
                minOverlap = overL;
                dir = ActorBase::DIR::LEFT; 
            }
            // 左に移動中の場合
            if (moveAmount.x < 0 && overR < minOverlap && pBottom >= tBottom) 
            {
                // 右へ押し戻す判定を有効にする
                minOverlap = overR;
                dir = ActorBase::DIR::RIGHT;
            }

            // 落下中の場合　
            if (moveAmount.y > 0 && overT < minOverlap)
            {
                // 上へ押し戻す判定を有効にする
                minOverlap = overT; 
                dir = ActorBase::DIR::UP;
                
                // 地面判定を設定
                owner_.SetIsGround(true);
            }
            // 上に移動中の場合　
            if (moveAmount.y < 0 && overB < minOverlap) 
            {
                // 下へ押し戻す判定を有効にする
                minOverlap = overB; 
                dir = ActorBase::DIR::DOWN;
            }

            // 決定した方向にのみ補正
            if (dir == ActorBase::DIR::LEFT) { pos.x -= (overL + 0.01f); owner_.SetMoveAmount(Vector2F(0.0f, moveAmount.y)); }
            else if (dir == ActorBase::DIR::RIGHT) { pos.x += (overR + 0.01f); owner_.SetMoveAmount(Vector2F(0.0f, moveAmount.y)); }
            else if (dir == ActorBase::DIR::UP) { pos.y -= (overT + 0.01f); owner_.SetMoveAmount(Vector2F(moveAmount.x, 0.0f)); }
            else if (dir == ActorBase::DIR::DOWN) { pos.y += (overB + 0.01f); owner_.SetMoveAmount(Vector2F(moveAmount.x, 0.0f)); }

            // 座標格納
            owner_.SetPosition(pos);
        }
    }
}

void OnHitPlayer::OnHitAvilityBox(const std::weak_ptr<ColliderBase>& opponentCollider)
{
    //const ActorBase& box = opponentCollider.lock()->GetOwner();
    //Vector2F moveAmount = owner_.GetParameter()->moveAmount;

}
