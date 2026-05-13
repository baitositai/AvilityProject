#include "../../Object/Common/Animation.h"
#include "../Utility/UtilityCommon.h"
#include "../Object/Character/Player.h"
#include "../Collider/ColliderArray.h"
#include "../Collider/ColliderBox.h"
#include "OnHitPlayerStamp.h"
#include "OnHitPlayer.h"


OnHitPlayer::OnHitPlayer(Player& owner) :
    OnHitCharacterBase(owner),
    owner_(owner)
{
    onHitMap_.emplace(CollisionTags::TAG::ENEMY_CLONE, [this](const std::weak_ptr<ColliderBase>& opponentCollider)
        {
            return OnHitEnemy(opponentCollider);
        });

    onHitPlayerStamp_ = std::make_unique<OnHitPlayerStamp>(owner_);
}

OnHitPlayer::~OnHitPlayer()
{
}

void OnHitPlayer::Update(const std::weak_ptr<ColliderBase>& opponentCollider)
{
    switch(opponentCollider.lock()->GetPartnerTag())
    {
        case CollisionTags::TAG::PLAYER:
            OnHitBase::Update(opponentCollider);
            break;

        case CollisionTags::TAG::PLAYER_AVILITY_STAMP:
            onHitPlayerStamp_->Update(opponentCollider);
            break;

        default:
            break;
	}
}

void OnHitPlayer::OnHitStage(const std::weak_ptr<ColliderBase>& opponentCollider)
{
    return;
}

void OnHitPlayer::OnHitEnemy(const std::weak_ptr<ColliderBase>& opponentCollider)
{
    // 共通処理
	OnHitAttack(opponentCollider);

    // コライダーの判定を無効化
    opponentCollider.lock()->SetIsActive(false);
}

void OnHitPlayer::AvilityShot(const std::weak_ptr<ColliderBase>& opponentCollider, const Vector2F& normal)
{
	// ショットベクトルを法線ベクトルで反射させる
    Vector2F dir = UtilityCommon::Reflect( owner_.GetShotVec(), normal);

	owner_.SetShotVec(dir);
}