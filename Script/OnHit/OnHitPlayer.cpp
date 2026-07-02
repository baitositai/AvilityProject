#include "../../Object/Common/Animation.h"
#include "../../Object/Item/ItemAvility.h"
#include "../../Object/Item/ItemFood.h"
#include "../../Object/Item/ItemTreasure.h"
#include "../../Factory/FactoryComponent.h"
#include "../../Component/Avility/ComponentAvilityBase.h"
#include "../../Manager/Common/SoundManager.h"
#include "../../Manager/Common/InputManager.h"
#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Game/ItemManager.h"
#include "../../Manager/Game/PlayerManager.h"
#include "../Utility/UtilityCommon.h"
#include "../Object/Character/Player.h"
#include "../Collider/ColliderArray.h"
#include "../Collider/ColliderBox.h"
#include "OnHitPlayerStamp.h"
#include "OnHitPlayerShot.h"
#include "OnHitPlayer.h"

OnHitPlayer::OnHitPlayer(Player& owner) :
    OnHitCharacterBase(owner),
    inputManager_(InputManager::GetInstance()),
    factoryComponent_(FactoryComponent::GetInstance()),
    owner_(owner)
{
    onHitMap_.emplace(CollisionTags::TAG::ENEMY_BASE, [this](const std::weak_ptr<ColliderBase>& opponentCollider){ return OnHitEnemy(opponentCollider); });
    onHitMap_.emplace(CollisionTags::TAG::ENEMY_MAID, [this](const std::weak_ptr<ColliderBase>& opponentCollider){ return OnHitEnemy(opponentCollider); });
	onHitMap_.emplace(CollisionTags::TAG::ITEM_AVILITY, [this](const std::weak_ptr<ColliderBase>& opponentCollider) { return OnHitItemAvility(opponentCollider); });
	onHitMap_.emplace(CollisionTags::TAG::ITEM_FOOD, [this](const std::weak_ptr<ColliderBase>& opponentCollider) { return OnHitItemFood(opponentCollider); });
	onHitMap_.emplace(CollisionTags::TAG::ITEM_TREASURE, [this](const std::weak_ptr<ColliderBase>& opponentCollider) { return OnHitItemTreasure(opponentCollider); });
	onHitMap_.emplace(CollisionTags::TAG::DOOR, [this](const std::weak_ptr<ColliderBase>& opponentCollider) { return OnHitDoor(opponentCollider); });
	onHitMap_.emplace(CollisionTags::TAG::ENEMY_ATTACK_NORMAL, [this](const std::weak_ptr<ColliderBase>& opponentCollider) { return OnHitAttack(opponentCollider); });
	onHitMap_.emplace(CollisionTags::TAG::BAMBOO, [this](const std::weak_ptr<ColliderBase>& opponentCollider) { return OnHitAttack(opponentCollider); });
	onHitMap_.emplace(CollisionTags::TAG::CHANGE_NEXT_AREA, [this](const std::weak_ptr<ColliderBase>& opponentCollider) { return OnHitNextArea(opponentCollider); });

    onHitPlayerStamp_ = std::make_unique<OnHitPlayerStamp>(owner_);
    onHitPlayerShot_ = std::make_unique<OnHitPlayerShot>(owner_);
}

OnHitPlayer::~OnHitPlayer()
{
}

void OnHitPlayer::Update(const std::weak_ptr<ColliderBase>& opponentCollider)
{
    switch(opponentCollider.lock()->GetPartnerTag())
    {
        case CollisionTags::TAG::PLAYER:
            OnHitCharacterBase::Update(opponentCollider);
            break;

        case CollisionTags::TAG::PLAYER_AVILITY_STAMP:
            onHitPlayerStamp_->Update(opponentCollider);
            break;

        case CollisionTags::TAG::PLAYER_AVILITY_SHOT:
            onHitPlayerShot_->Update(opponentCollider);
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
    // 衝突者が無敵のときは無視
    if (owner_.IsInvincible())
    {
        return;
    }

    // ノックバック処理
    KnockBack(opponentCollider, KNOCK_BACK_FORCE);

    // ダメージ処理
    Damage(opponentCollider, DAMAGE_HIT_ENEMY);
}

void OnHitPlayer::OnHitItemAvility(const std::weak_ptr<ColliderBase>& opponentCollider)
{	
    owner_.GetParameter().isHitItem_ = true;
    if (inputManager_.IsTrgDown(InputManager::TYPE::PLAYER_GET_ITEM, owner_.GetParameter().padNo_))
    {
        // 衝突相手の所有者をキャストしてアイテムのインスタンスを取得
        const auto& item = dynamic_cast<const ItemBase*>(&opponentCollider.lock()->GetOwner());

        // アイテムのアビリティを取得
        const auto& itemAvility = dynamic_cast<const ItemAvility*>(item);

        auto componentAvility = factoryComponent_.CreateComponentAvility(itemAvility->GetCreateAvilityName(), owner_);

        // リソース番号指定
        componentAvility->SetAvilityResourceIndex(itemAvility->GetAvilityItemResourceIndex());
        
        // アイテムの種類を獲得
        owner_.SetAvilityComponent(std::move(componentAvility));
    }
}

void OnHitPlayer::OnHitItemFood(const std::weak_ptr<ColliderBase>& opponentCollider)
{
    owner_.GetParameter().isHitItem_ = true;
    if (inputManager_.IsTrgDown(InputManager::TYPE::PLAYER_GET_ITEM, owner_.GetParameter().padNo_))
    {
        // 衝突相手の所有者をキャストしてアイテムのインスタンスを取得
        const auto& item = dynamic_cast<const ItemBase*>(&opponentCollider.lock()->GetOwner());

        // アイテムのアビリティを取得
        const auto& itemFood = dynamic_cast<const ItemFood*>(item);

        // アイテムの種類を獲得
        owner_.Heal(itemFood->GetParameter().heal_);
    }
}

void OnHitPlayer::OnHitItemTreasure(const std::weak_ptr<ColliderBase>& opponentCollider)
{
    owner_.GetParameter().isHitItem_ = true;
}

void OnHitPlayer::OnHitDoor(const std::weak_ptr<ColliderBase>& opponentCollider)
{
    if (InputManager::GetInstance().IsTrgDown(InputManager::TYPE::PLAYER_ENTER_DOOR, owner_.GetParameter().padNo_))
    {
        // 入室状態へ遷移
        owner_.ChangeState(Player::STATE::ENTER);

        // 全てのアビリティ処理を無効
        owner_.SetAllAvilityComponentActive(false);
    }
}

void OnHitPlayer::OnHitNextArea(const std::weak_ptr<ColliderBase>& opponentCollider)
{
    // シーン遷移
    SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);

    // コライダーの判定を消す
    opponentCollider.lock()->SetIsActive(false);

    // プレイヤーのアニメーションを再生
    owner_.GetAnimation().Play(Animation::TYPE::WALK);

    // BGM停止
    SoundManager& sndMng = SoundManager::GetInstance();
    sndMng.StopBgm(SoundType::BGM::TRAIN);
    sndMng.StopBgm(SoundType::BGM::TRAIN_ROOM);

    // 汽笛
    sndMng.PlaySe(SoundType::SE::TRAIN_WHISTLE);
}

void OnHitPlayer::AvilityShot(const std::weak_ptr<ColliderBase>& opponentCollider, const Vector2F& normal)
{
    // パラメータ取得
    ParameterPlayer& parameter = owner_.GetParameter();

	// ショットベクトルを法線ベクトルで反射させる
    parameter.shotVec_ = UtilityCommon::Reflect(parameter.shotVec_, normal);
}