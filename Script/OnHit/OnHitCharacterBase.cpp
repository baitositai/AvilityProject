#include "../Utility/UtilityCommon.h"
#include "../Collider/ColliderArray.h"
#include "../Collider/ColliderBox.h"
#include "../Object/ActorBase.h"
#include "../Object/Common/Animation.h"
#include "../Object/Character/CharacterBase.h"
#include "OnHitCharacterBase.h"

OnHitCharacterBase::OnHitCharacterBase(CharacterBase& owner) :
    OnHitBase(owner),
    owner_(owner)
{
    onHitMap_.emplace(CollisionTags::TAG::STAGE, [this](const std::weak_ptr<ColliderBase>& opponentCollider)
        {
            return OnHitStage(opponentCollider);
        });
    onHitMap_.emplace(CollisionTags::TAG::AVILITY_BOX, [this](const std::weak_ptr<ColliderBase>& opponentCollider)
        {
            return OnHitAvilityBox(opponentCollider);
        });
}


OnHitCharacterBase::~OnHitCharacterBase()
{
}

void OnHitCharacterBase::OnHitStage(const std::weak_ptr<ColliderBase>& opponentCollider)
{
    auto collider = std::dynamic_pointer_cast<ColliderArray>(opponentCollider.lock());
    if (!collider)
    {
        return;
    }

    const auto& indexes = collider->GetResult().indexes;
    if (indexes.empty())
    {
        return;
    }

    Vector2F pos = owner_.GetParameter()->pos;
    Vector2 boxSize = owner_.GetHitBoxSize();
    Vector2 chipSize = collider->GetChipSize();
    // 現在の重力方向を取得 (例としてVector2F。下なら(0, 1), 左なら(-1, 0)など)
    Vector2F gravityDir = owner_.GetGravityDirectionVector();

    for (const Vector2& index : indexes)
    {
        Vector2F moveAmount = owner_.GetParameter()->moveAmount;

        if (moveAmount.x == 0.0f && moveAmount.y == 0.0f)
        {
            break;
        }

        float tLeft = index.x * chipSize.x;
        float tRight = tLeft + chipSize.x;
        float tTop = index.y * chipSize.y;
        float tBottom = tTop + chipSize.y;

        float pLeft = pos.x - boxSize.x / 2.0f;
        float pRight = pos.x + boxSize.x / 2.0f;
        float pTop = pos.y - boxSize.y / 2.0f;
        float pBottom = pos.y + boxSize.y / 2.0f;

        float overL = pRight - tLeft;
        float overR = tRight - pLeft;
        float overT = pBottom - tTop;
        float overB = tBottom - pTop;

        if (overL > 0 && overR > 0 && overT > 0 && overB > 0)
        {
            float minOverlap = 10000.0f;
            ActorBase::DIR pushDir = ActorBase::DIR::MAX;
            Vector2F normal(0.0f, 0.0f);

            // X軸の押し戻し判定
            if (moveAmount.x > 0 && overL < minOverlap)
            {
                minOverlap = overL;
                pushDir = ActorBase::DIR::LEFT;
                normal.x = -1.0f;
            }
            else if (moveAmount.x < 0 && overR < minOverlap)
            {
                minOverlap = overR;
                pushDir = ActorBase::DIR::RIGHT;
                normal.x = 1.0f;
            }

            // Y軸の押し戻し判定 (より浅いめり込みがあれば上書き)
            if (moveAmount.y > 0 && overT < minOverlap)
            {
                minOverlap = overT;
                pushDir = ActorBase::DIR::UP;
                normal.x = 0.0f; // X軸の判定をリセット
                normal.y = -1.0f;
            }
            else if (moveAmount.y < 0 && overB < minOverlap)
            {
                minOverlap = overB;
                pushDir = ActorBase::DIR::DOWN;
                normal.x = 0.0f;
                normal.y = 1.0f;
            }

            // 位置補正と速度修正
            if (pushDir != ActorBase::DIR::MAX)
            {
                const float epsilon = 0.01f;
                if (normal.x != 0.0f)
                {
                    pos.x += (minOverlap + epsilon) * normal.x;
                    moveAmount.x = 0.0f;
                }
                else if (normal.y != 0.0f)
                {
                    pos.y += (minOverlap + epsilon) * normal.y;
                    moveAmount.y = 0.0f;
                }

                // 接地判定: 押し戻し方向(normal)が重力方向と逆なら接地とみなす
                // 例: 重力が下(0, 1)で、押し戻しが上(0, -1)なら内積は-1
                if (normal.x * gravityDir.x + normal.y * gravityDir.y < -0.5f)
                {
                    owner_.SetIsGround(true);
                }

                owner_.SetPosition(pos);
                owner_.SetMoveAmount(moveAmount);
            }
        }
    }
}

void OnHitCharacterBase::OnHitAvilityBox(const std::weak_ptr<ColliderBase>& opponentCollider)
{
    auto collider = std::dynamic_pointer_cast<ColliderBox>(opponentCollider.lock());

    const auto& opOwner = opponentCollider.lock()->GetOwner();

    //お互いのパラメータ
    const ActorBase::Parameter* myParam = owner_.GetParameter();
    const ActorBase::Parameter* opParam = opOwner.GetParameter();


    //互いの重さ
    float myWeight = myParam->weight;
    float opWeight = opParam->weight;
    float weightTotal = myWeight + opWeight;
    float weightRatio = myWeight / weightTotal;

    //お互いの距離
    Vector2F diff = Vector2F::SubVector2F(opParam->pos, myParam->pos);
    int signX = UtilityCommon::GetSign(diff.x);
    int signY = UtilityCommon::GetSign(diff.y);

    //それぞれのめり込み量
    float overlapX = static_cast<float>(owner_.GetHitBoxSize().x / 2)
        + static_cast<float>(collider->GetBoxHalfSize().x) - fabsf(diff.x);
    float overlapY = static_cast<float>(owner_.GetHitBoxSize().y / 2)
        + static_cast<float>(collider->GetBoxHalfSize().y) - fabsf(diff.y);

    //移動量
    Vector2F moveAmount = myParam->moveAmount;

    //ボックスの上に乗っているかを判断
    Vector2F pos = myParam->pos;

    //ボックスの上に乗っていたら地面判定を付与
    if (overlapX >= overlapY)
    {
        pos.y -= (overlapY + 0.01f) * signY;
        // 地面判定を設定
        owner_.SetIsGround(true);

        //落下を防止するためにYの移動量をゼロにする
        moveAmount.y = 0;
        owner_.SetMoveAmount(moveAmount);
    }
    else
    {
        //ボックスを押し出す
        pos.x += overlapX * -weightRatio * signX;

    }

    //座標更新
    owner_.SetPosition(pos);
}

void OnHitCharacterBase::OnHitAttack(const std::weak_ptr<ColliderBase>& opponentCollider)
{
    // 衝突者が無敵のときは無視
    if (owner_.IsInvincible() || opponentCollider.lock()->GetPartnerTag() == CollisionTags::TAG::PLAYER_ATTACK_NORMAL)
    {
        return;
    }

    // 所有者情報の取得
    const auto& ownerRef = opponentCollider.lock()->GetOwner();

    // 攻撃者から自分へのベクトルを計算する
    Vector2F attackerPos = opponentCollider.lock()->GetOwner().GetParameter()->pos;
    Vector2F myPos = owner_.GetParameter()->pos;
    Vector2F direction = Vector2F::SubVector2F(myPos, attackerPos);

    // ゼロ除算防止のガード
    if (direction.Length() < 0.0001f)
    {
        direction = Vector2F(0.0f, -1.0f);
    }

    // 左右方向の決定 (自分と相手の座標差から符号だけ取る)
    float knockBackDirX = (direction.x > 0) ? 1.0f : -1.0f;

    // パワーの決定
    // 横方向は勢いよく、縦方向は「ぴょん」と跳ねるような固定値を加える
    float HORIZONTAL_FORCE = 600.0f; // 横への吹き飛び力
    float VERTICAL_LAUNCH = -500.0f; // 上への跳ね上げ力 (DXライブラリ等の座標系ならマイナスが上)

    Vector2F finalPower = Vector2F(knockBackDirX * HORIZONTAL_FORCE, VERTICAL_LAUNCH);

    // パワーをセットする
    owner_.SetKnockBackPower(finalPower);

    // ダメージ処理
    auto charaPtr = dynamic_cast<const CharacterBase*>(&ownerRef);
    if (charaPtr != nullptr)
    {
        int damage = charaPtr->GetAttackPower();
        owner_.Damage(damage);
    }

    // 地面判定無効
    owner_.SetIsGround(false);
}
