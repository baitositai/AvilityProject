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
    auto collider = opponentCollider.lock();
    if (!collider) return;

    // GetOwner() が const を返す設計なら、非 const 版の取得メソッドがあるか確認してください。
    // もしなければ、以下のように const_cast を使うか、設計を見直します。
    auto& opOwner = const_cast<ActorBase&>(collider->GetOwner());

    // キャスト先も CharacterBase* (非const) に合わせる
    auto* charaPtr = dynamic_cast<CharacterBase*>(&opOwner);

    if (charaPtr)
    {
		// ダメージ処理
        charaPtr->Damage(owner_.GetAttackPowerWithBoost());    
        
        // 無敵にする
        owner_.SetIsInvincibleTime(INVINCIBLE_TIME);

        if (charaPtr->GetState() == CharacterBase::STATE::DEAD)
        {
            return;
        }
    }

    // ノックバック処理
    KnockBack(opponentCollider, Vector2F(0.0f,KNOCK_BACK_FORCE_STRONG.y));

    // 重力をもとに戻す
    owner_.SetGravityPower(owner_.GetParameter()->gravityPower - ComponentAvilityStamp::ACC_GRAVITY);

    // キャラクターの入力処理を有効にする
    owner_.SetStateComponentActive(Player::STATE::ALIVE, true);

    // 所有者のコライダーの判定を有効にする
    owner_.SetColliderActive(true);
}