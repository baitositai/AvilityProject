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
    if (!collider) return;              // コライダーが空の場合終了

    // 当たったすべてのタイルインデックスを取得
    const auto& indexes = collider->GetResult().indexes;
    if (indexes.empty()) return;       // インデックスリストが空の場合終了

    Vector2F pos = owner_.GetParameter()->pos;          // 座標取得
    Vector2 boxSize = owner_.GetHitBoxSize();           // ボックスサイズ
    Vector2 chipSize = collider->GetChipSize();         // チップサイズ

    float bestOverlap = 10000.0f;
    Vector2F bestNormal(0.0f, 0.0f);

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
            Vector2F normal = Vector2F(0.0f, 0.0f);    // 法線ベクトル

            // 右に移動中の場合
            if (moveAmount.x > 0 && overL < minOverlap)
            {
                // 左へ押し戻す判定を有効にする
                minOverlap = overL;
                dir = ActorBase::DIR::LEFT;
                normal = Vector2F(-1.0f, 0.0f);
            }
            // 左に移動中の場合
            if (moveAmount.x < 0 && overR < minOverlap && pBottom >= tBottom)
            {
                // 右へ押し戻す判定を有効にする
                minOverlap = overR;
                dir = ActorBase::DIR::RIGHT;
                normal = Vector2F(1.0f, 0.0f);
            }

            // 落下中の場合　
            if (moveAmount.y > 0 && overT < minOverlap)
            {
                // 上へ押し戻す判定を有効にする
                minOverlap = overT;
                dir = ActorBase::DIR::UP;
                normal = Vector2F(0.0f, -1.0f);

                // 地面判定を設定
                owner_.SetIsGround(true);
            }
            // 上に移動中の場合　
            if (moveAmount.y < 0 && overB < minOverlap)
            {
                // 下へ押し戻す判定を有効にする
                minOverlap = overB;
                dir = ActorBase::DIR::DOWN;
                normal = Vector2F(0.0f, 1.0f);
            }

            if (minOverlap < bestOverlap)
            {
                bestOverlap = minOverlap;
                bestNormal = normal;
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
    float weightDiff = myWeight - opWeight;

    //お互いの距離
    Vector2F diff = Vector2F::SubVector2F(opParam->pos, myParam->pos);
    int signX = UtilityCommon::GetSign(diff.x);
    int signY = UtilityCommon::GetSign(diff.y);

    float overlap = static_cast<float>(owner_.GetHitBoxSize().x / 2.0f)
        + static_cast<float>(collider->GetBoxHalfSize().x) - fabsf(diff.x) + myParam->moveAmount.x;

    Vector2F moveAmount = Vector2F();
    moveAmount.x = overlap * -weightDiff * signX;
    moveAmount.y = 0.0f;

    owner_.SetMoveAmount(moveAmount);
}

void OnHitCharacterBase::OnHitAttack(const std::weak_ptr<ColliderBase>& opponentCollider)
{
    // 衝突者が無敵のときは無視
    if (owner_.IsInvincible() || opponentCollider.lock()->GetPartnerTag() == CollisionTags::TAG::PLAYER_ATTACK_NORMAL) return;

    // 所有者情報の取得
    const auto& ownerRef = opponentCollider.lock()->GetOwner();

    // 攻撃者から自分へのベクトルを計算する
    Vector2F attackerPos = opponentCollider.lock()->GetOwner().GetParameter()->pos;
    Vector2F myPos = owner_.GetParameter()->pos;
    Vector2F direction = Vector2F::SubVector2F(myPos, attackerPos);

    // ゼロ除算防止のガード
    if (direction.Length() < 0.0001f)
    {
        direction = Vector2F(0.0f, -0.5f);
    }

    // 基本となるノックバック方向を正規化して取得
    Vector2F normalizedDir = direction.Normalize();

    float horizontalWeight = 1.5f;
    normalizedDir.x *= horizontalWeight;

    // 重力の影響を打ち消すための上向きベクトルを加算する
    // 重力が常に下向き（0, 1）ならその逆方向（0, -1）を足す
    Vector2F gravityResist = Vector2F(0.0f, -0.5f);
    Vector2F finalDir = Vector2F::AddVector2F(normalizedDir, gravityResist);

    // 加算によって長さが変わるため再度正規化する
    finalDir = finalDir.Normalize();

    // 最終的なノックバックパワーを決定する
    float power = 450.0f;
    Vector2F finalPower = Vector2F::MulVector2F(finalDir, Vector2F(power, power));

    // パワーをセットする
    owner_.SetKnockBackPower(finalPower);
    
    // アニメション設定
    owner_.GetAnimation().Play(Animation::TYPE::DAMAGE, false);

    // 次回アニメーション設定
    owner_.GetAnimation().SetNextAnimationType(Animation::TYPE::IDLE);

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
