#include "../../Object/Common/Animation.h"
#include "../../Object/Item/ItemAvility.h"
#include "../../Factory/FactoryComponent.h"
#include "../../Component/Avility/ComponentAvilityBase.h"
#include "../Utility/UtilityCommon.h"
#include "../Object/Character/Player.h"
#include "../Collider/ColliderArray.h"
#include "../Collider/ColliderBox.h"
#include "OnHitPlayerStamp.h"
#include "OnHitPlayer.h"


OnHitPlayer::OnHitPlayer(Player& owner) :
    OnHitCharacterBase(owner),
    factoryComponent_(FactoryComponent::GetInstance()),
    owner_(owner)
{
    onHitMap_.emplace(CollisionTags::TAG::ENEMY_CLONE, [this](const std::weak_ptr<ColliderBase>& opponentCollider){ return OnHitEnemy(opponentCollider); });
	onHitMap_.emplace(CollisionTags::TAG::ITEM_AVILITY, [this](const std::weak_ptr<ColliderBase>& opponentCollider) { return OnHitItemAvility(opponentCollider); });

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
}

void OnHitPlayer::OnHitItemAvility(const std::weak_ptr<ColliderBase>& opponentCollider)
{	
    // 衝突相手の所有者をキャストしてアイテムのインスタンスを取得
	const auto& item = dynamic_cast<const ItemBase*>(&opponentCollider.lock()->GetOwner());

	// アイテムのアビリティを取得
	const auto& itemAvility = dynamic_cast<const ItemAvility*>(item);

    // アイテムの種類を獲得
    owner_.SetAbilityComponent(std::move(factoryComponent_.CreateComponentAvility(itemAvility->GetCreateAvilityName(), owner_)));
}

void OnHitPlayer::AvilityShot(const std::weak_ptr<ColliderBase>& opponentCollider, const Vector2F& normal)
{
    // パラメータ取得
    ParameterPlayer& parameter = owner_.GetParameter();

	// ショットベクトルを法線ベクトルで反射させる
    parameter.shotVec_ = UtilityCommon::Reflect(parameter.shotVec_, normal);
}