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
    return;
}

void OnHitPlayer::OnHitEnemy(const std::weak_ptr<ColliderBase>& opponentCollider)
{
    // 攻撃判定
    OnHitAttack(opponentCollider);
}

void OnHitPlayer::AvilityShot(const std::weak_ptr<ColliderBase>& opponentCollider, const Vector2F& normal)
{
	// ショットベクトルを法線ベクトルで反射させる
    Vector2F dir = UtilityCommon::Reflect( owner_.GetShotVec(), normal);

	owner_.SetShotVec(dir);
}