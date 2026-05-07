#include "../../Object/Common/Animation.h"
#include "../Utility/UtilityCommon.h"
#include "../Object/Character/Player.h"
#include "../Collider/ColliderArray.h"
#include "../Collider/ColliderBox.h"
#include "OnHitPlayer.h"


OnHitPlayer::OnHitPlayer(Player& owner) :
    OnHitCharacterBase(owner),
    owner_(owner)
{
    onHitMap_.emplace(CollisionTags::TAG::ENEMY_CLONE, [this](const std::weak_ptr<ColliderBase>& opponentCollider)
        {
            return OnHitEnemy(opponentCollider);
        });
}

OnHitPlayer::~OnHitPlayer()
{
}

void OnHitPlayer::OnHitStage(const std::weak_ptr<ColliderBase>& opponentCollider)
{
    auto collider = std::dynamic_pointer_cast<ColliderArray>(opponentCollider.lock());
    if (!collider) return;

    const auto& indexes = collider->GetResult().indexes;
    if (indexes.empty()) return;

    Vector2F pos = owner_.GetParameter()->pos;
    Vector2 boxSize = owner_.GetHitBoxSize();
    Vector2 chipSize = collider->GetChipSize();
    Vector2F moveAmount = owner_.GetParameter()->moveAmount;
    ActorBase::DIR gDir = owner_.GetParameter()->gravityDir;

    if (moveAmount.x == 0.0f && moveAmount.y == 0.0f) return;

    float bestOverlap = 10000.0f;
    Vector2F bestNormal(0.0f, 0.0f);

    for (const Vector2& index : indexes)
    {
        // タイル・プレイヤーの境界計算
        float tLeft = index.x * chipSize.x;
        float tRight = tLeft + chipSize.x;
        float tTop = index.y * chipSize.y;
        float tBottom = tTop + chipSize.y;

        float pLeft = pos.x - boxSize.x / 2.0f;
        float pRight = pos.x + boxSize.x / 2.0f;
        float pTop = pos.y - boxSize.y / 2.0f;
        float pBottom = pos.y + boxSize.y / 2.0f;

        float overlaps[4] = { pRight - tLeft, tRight - pLeft, pBottom - tTop, tBottom - pTop };

        // 全ての面でめり込みがあるか（矩形交差判定）
        if (overlaps[0] > 0 && overlaps[1] > 0 && overlaps[2] > 0 && overlaps[3] > 0)
        {
            float minOverlap = 10000.0f;
            ActorBase::DIR pushDir = ActorBase::DIR::MAX;
            Vector2F currentNormal(0.0f, 0.0f);

            // 移動方向に基づいた最小めり込みの特定
            if (moveAmount.x > 0 && overlaps[0] < minOverlap) { minOverlap = overlaps[0]; pushDir = ActorBase::DIR::LEFT;  currentNormal = { -1.0f, 0.0f }; }
            if (moveAmount.x < 0 && overlaps[1] < minOverlap && pBottom >= tBottom) { minOverlap = overlaps[1]; pushDir = ActorBase::DIR::RIGHT; currentNormal = { 1.0f, 0.0f }; }
            if (moveAmount.y > 0 && overlaps[2] < minOverlap) { minOverlap = overlaps[2]; pushDir = ActorBase::DIR::UP;    currentNormal = { 0.0f, -1.0f }; }
            if (moveAmount.y < 0 && overlaps[3] < minOverlap) { minOverlap = overlaps[3]; pushDir = ActorBase::DIR::DOWN;  currentNormal = { 0.0f, 1.0f }; }

            if (pushDir == ActorBase::DIR::MAX) continue;

            // 接地判定 (重力方向と押し戻し方向が逆なら地面)
            bool isGround = false;
            if (gDir == ActorBase::DIR::DOWN && pushDir == ActorBase::DIR::UP)    isGround = true;
            else if (gDir == ActorBase::DIR::UP && pushDir == ActorBase::DIR::DOWN)  isGround = true;
            else if (gDir == ActorBase::DIR::LEFT && pushDir == ActorBase::DIR::RIGHT) isGround = true;
            else if (gDir == ActorBase::DIR::RIGHT && pushDir == ActorBase::DIR::LEFT)  isGround = true;

            if (isGround) owner_.SetIsGround(true);

            // 反射用情報の更新（最も浅いものを採用）
            if (minOverlap < bestOverlap)
            {
                bestOverlap = minOverlap;
                bestNormal = currentNormal;
            }

            // 座標補正と速度減衰
            const float epsilon = 0.01f;
            switch (pushDir)
            {
            case ActorBase::DIR::LEFT:  pos.x -= (overlaps[0] + epsilon); owner_.SetMoveAmount({ 0.0f, moveAmount.y }); break;
            case ActorBase::DIR::RIGHT: pos.x += (overlaps[1] + epsilon); owner_.SetMoveAmount({ 0.0f, moveAmount.y }); break;
            case ActorBase::DIR::UP:    pos.y -= (overlaps[2] + epsilon); owner_.SetMoveAmount({ moveAmount.x, 0.0f }); break;
            case ActorBase::DIR::DOWN:  pos.y += (overlaps[3] + epsilon); owner_.SetMoveAmount({ moveAmount.x, 0.0f }); break;
            }
            owner_.SetPosition(pos);
        }
    }

    AvilityShot(opponentCollider, bestNormal);
}

void OnHitPlayer::OnHitEnemy(const std::weak_ptr<ColliderBase>& opponentCollider)
{
    // 攻撃判定
    OnHitAttack(opponentCollider);
}

void OnHitPlayer::AvilityShot(const std::weak_ptr<ColliderBase>& opponentCollider, const Vector2F& normal)
{
    // 地面にいたら反射させない
    /*if(owner_.IsGround()) {
        return;
	}*/


	// ショットベクトルを法線ベクトルで反射させる
    Vector2F dir = UtilityCommon::Reflect( owner_.GetShotVec(), normal);


	owner_.SetShotVec(dir);
}