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
    auto collider = std::dynamic_pointer_cast<ColliderArray>(opponentCollider.lock());
    if (!collider) return;

    // 当たったすべてのタイルインデックスを取得
    const auto& hitIndexes = collider->GetResult().hitIndexes;
    if (hitIndexes.empty()) return;

    Vector2F pos = owner_.GetParameter()->pos;
   // Vector2F moveAmount = owner_.GetParameter()->moveAmount;
    Vector2 boxSize = owner_.GetHitBoxSize();
    Vector2 chipSize = collider->GetChipSize();

    for (const auto& hitIndex : hitIndexes)
    {
        Vector2F moveAmount = owner_.GetParameter()->moveAmount;

        if (moveAmount.x == 0.0f && moveAmount.y == 0.0f)
        {
            break;
        }

        // 1. ボックス化（座標化）
        float tLeft = hitIndex.x * chipSize.x;
        float tRight = tLeft + chipSize.x;
        float tTop = hitIndex.y * chipSize.y;
        float tBottom = tTop + chipSize.y;

        // プレイヤーの四端
        float pLeft = pos.x - boxSize.x / 2.0f;
        float pRight = pos.x + boxSize.x / 2.0f;
        float pTop = pos.y - boxSize.y / 2.0f;
        float pBottom = pos.y + boxSize.y / 2.0f;

        // 2. どのくらいめり込んでいるか（ボックス同士の重なり）
        float overL = pRight - tLeft;
        float overR = tRight - pLeft;
        float overT = pBottom - tTop;
        float overB = tBottom - pTop;

        // 3. 最小のめり込み（一番浅い方向）を探して、その方向にだけ押し出す
        // こうすれば、地面のチップで「横押し出し」が暴走することはありません
        //float minOverlap = FLT_MAX;
        //int dir = -1; // 0:左, 1:右, 2:上, 3:下

        if (overL > 0 && overR > 0 && overT > 0 && overB > 0)
        {
            float minOverlap = 10000.0f;
            int dir = -1;

            // 【ここが重要】移動方向と矛盾しない押し出し方向だけを候補に入れる

            // 1. 右に移動中なら、左へ押し戻す判定を有効にする
            if (moveAmount.x > 0 && overL < minOverlap) { minOverlap = overL; dir = 0; }

            // 2. 左に移動中なら、右へ押し戻す判定を有効にする
            if (moveAmount.x < 0 && overR < minOverlap) { 
                minOverlap = overR; dir = 1; }

            // 3. 下に移動（落下）中なら、上へ押し戻す（床）判定を有効にする
            if (moveAmount.y > 0 && overT < minOverlap) { minOverlap = overT; dir = 2; }

            // 4. 上に移動中なら、下へ押し戻す（天井）判定を有効にする
            if (moveAmount.y < 0 && overB < minOverlap) { minOverlap = overB; dir = 3; }

            // 決定した方向にのみ補正
            if (dir == 0) { pos.x -= (overL + 0.01f); owner_.SetMoveAmount(Vector2F(0.0f, moveAmount.y)); }
            else if (dir == 1) { pos.x += (overR + 0.01f); owner_.SetMoveAmount(Vector2F(0.0f, moveAmount.y)); }
            else if (dir == 2) { pos.y -= (overT + 0.01f); owner_.SetMoveAmount(Vector2F(moveAmount.x, 0.0f)); }
            else if (dir == 3) { pos.y += (overB + 0.01f); owner_.SetMoveAmount(Vector2F(moveAmount.x, 0.0f)); }

            owner_.SetPosition(pos);
        }
    }

    // 衝突結果リセット
    collider->SetResult(ColliderArray::Result());
}