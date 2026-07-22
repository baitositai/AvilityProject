#include "../../Component/Avility/ComponentAvilityStamp.h"
#include "../../Collider/ColliderBase.h"
#include "../../Object/Character/CharacterBase.h"
#include "../../Object/Character/Player.h"
#include "OnHitPlayerStamp.h"

OnHitPlayerStamp::OnHitPlayerStamp(Player& owner) :
	OnHitCharacterBase(owner),
	owner_(owner)
{
}

OnHitPlayerStamp::~OnHitPlayerStamp()
{
}

void OnHitPlayerStamp::Update(const std::weak_ptr<ColliderBase>& opponentCollider)
{
    // 相手コライダーがあるか確認
    auto collider = opponentCollider.lock();
    if (!collider) return;

    //　相手コライダーの所有者を取得
    auto& opponentOwner = collider->GetOwner();

    // 相手のダメージ処理
    opponentOwner.Damage(owner_.GiveDamage(), collider->GetHitPos());

    // 自身無敵にする
    owner_.GetParameter().invincibleTime_ = INVINCIBLE_TIME;

    // 相手のHPが0より大きい場合
    if (opponentOwner.GetParameter().hp_ > 0)
    {
        // ノックバック処理
        KnockBack(opponentCollider, Vector2F(0.0f, KNOCK_BACK_FORCE_STRONG.y));

        // キャラクターの入力処理を有効にする
        owner_.SetStateComponentActive(Player::STATE::ALIVE, true);

        // 所有者のコライダーの判定を有効にする
        owner_.SetColliderActive(true);
    }
}