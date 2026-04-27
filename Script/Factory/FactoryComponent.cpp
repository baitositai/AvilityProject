#include "../../Component/ComponentBase.h"
#include "../../Component/ComponentMove.h"
#include "../../Component/ComponentSpriteAnimation.h"
#include "../../Component/ComponentGravity.h"
#include "../../Component/ComponentKnockBack.h"
#include "../../Component/Avility/ComponentAvilityBox.h"
#include "../../Component/Avility/ComponentAvilityShot.h"
#include "../../Component/State/Player/ComponentStatePlayerAttack.h"
#include "../../Component/State/Player/ComponentStatePlayerDead.h"
#include "../../Component/State/Player/ComponentStatePlayerHit.h"
#include "../../Component/State/Player/ComponentStatePlayerRespawn.h"
#include "../../Component/State/Player/ComponentStatePlayerAlive.h"
#include "../../Component/State/EnemyClone/ComponentStateEnemyAlive.h"
#include "../../Object/Character/CharacterBase.h" 
#include "../../Object/Character/Player.h" 
#include "../../Object/ActorBase.h" 
#include "FactoryComponent.h"

std::unique_ptr<ComponentBase> FactoryComponent::CreateComponent(const std::string& name, ActorBase& owner)
{
    // 必要とするものがあるか探索
    auto it = componentCreateMap_.find(name);

    // ある場合
    if (it != componentCreateMap_.end())
    {
        // 生成したものを返す
        return it->second(owner);
    }

    // 見つからない場合空で返す
    return nullptr;
}

std::unique_ptr<ComponentMove> FactoryComponent::CreateComponentMove(ActorBase& owner)
{
    return std::make_unique<ComponentMove>(owner);
}

std::unique_ptr<ComponentSpriteAnimation> FactoryComponent::CreateComponentSpriteAnimation(ActorBase& owner)
{
    return std::make_unique<ComponentSpriteAnimation>(owner);
}

std::unique_ptr<ComponentGravity> FactoryComponent::CreateComponentGravity(ActorBase& owner)
{
    return std::make_unique<ComponentGravity>(owner);
}



std::unique_ptr<ComponentStatePlayerAlive> FactoryComponent::CreateComponentStatePlayerAlive(ActorBase& owner)
{
    auto* playerPtr = dynamic_cast<Player*>(&owner);

    if (playerPtr == nullptr)
    {
        // キャストに失敗した場合nullptrを返す
        return nullptr;
    }
    return std::make_unique<ComponentStatePlayerAlive>(*playerPtr);
}

std::unique_ptr<ComponentStatePlayerAttack> FactoryComponent::CreateComponentStatePlayerAttack(ActorBase& owner)
{
    auto* playerPtr = dynamic_cast<Player*>(&owner);

    if (playerPtr == nullptr)
    {
        // キャストに失敗した場合nullptrを返す
        return nullptr;
    }
    return std::make_unique<ComponentStatePlayerAttack>(*playerPtr);
}

std::unique_ptr<ComponentStatePlayerDead> FactoryComponent::CreateComponentStatePlayerDead(ActorBase& owner)
{
    auto* playerPtr = dynamic_cast<Player*>(&owner);

    if (playerPtr == nullptr)
    {
        // キャストに失敗した場合nullptrを返す
        return nullptr;
    }
    return std::make_unique<ComponentStatePlayerDead>(*playerPtr);
}

std::unique_ptr<ComponentStatePlayerHit> FactoryComponent::CreateComponentStatePlayerHit(ActorBase& owner)
{
    auto* playerPtr = dynamic_cast<Player*>(&owner);

    if (playerPtr == nullptr)
    {
        // キャストに失敗した場合nullptrを返す
        return nullptr;
    }
    return std::make_unique<ComponentStatePlayerHit>(*playerPtr);
}

std::unique_ptr<ComponentStatePlayerRespawn> FactoryComponent::CreateComponentStatePlayerRespawn(ActorBase& owner)
{
    auto* playerPtr = dynamic_cast<Player*>(&owner);

    if (playerPtr == nullptr)
    {
        // キャストに失敗した場合nullptrを返す
        return nullptr;
    }
    return std::make_unique<ComponentStatePlayerRespawn>(*playerPtr);
}

std::unique_ptr<ComponentStateEnemyAlive> FactoryComponent::CreateComponentStateEnemyAlive(ActorBase& owner)
{
    auto* charaPtr = dynamic_cast<CharacterBase*>(&owner);

    if (charaPtr == nullptr)
    {
        // キャストに失敗した場合nullptrを返す
        return nullptr;
    }
    return std::make_unique<ComponentStateEnemyAlive>(*charaPtr);
}

std::unique_ptr<ComponentAvilityBox> FactoryComponent::CreateComponentAvilityBox(ActorBase& owner)
{
    auto* playerPtr = dynamic_cast<Player*>(&owner);

    if (playerPtr == nullptr)
    {
        // キャストに失敗した場合nullptrを返す
        return nullptr;
    }
    return std::make_unique<ComponentAvilityBox>(*playerPtr);
}

std::unique_ptr<ComponentAvilityShot> FactoryComponent::CreateComponentAvilityShot(ActorBase& owner)
{
    auto* playerPtr = dynamic_cast<Player*>(&owner);

    if (playerPtr == nullptr)
    {
        // キャストに失敗した場合nullptrを返す
        return nullptr;
    }
    return std::make_unique<ComponentAvilityShot>(*playerPtr);
}

std::unique_ptr<ComponentKnockBack> FactoryComponent::CreateComponentKnockBack(ActorBase& owner)
{
    auto* charaPtr = dynamic_cast<CharacterBase*>(&owner);

    if (charaPtr == nullptr)
    {
        // キャストに失敗した場合nullptrを返す
        return nullptr;
    }
    return std::make_unique<ComponentKnockBack>(*charaPtr);
}

FactoryComponent::FactoryComponent()
{
    // 生成処理の登録
    componentCreateMap_.emplace("move", [this](ActorBase& owner)
        {
            return CreateComponentMove(owner);
        });
    componentCreateMap_.emplace("spriteAnimation", [this](ActorBase& owner)
        {
            return CreateComponentSpriteAnimation(owner);
        });
    componentCreateMap_.emplace("gravity", [this](ActorBase& owner)
        {
            return CreateComponentGravity(owner);
        });
    componentCreateMap_.emplace("playerAlive", [this](ActorBase& owner)
        {
            return CreateComponentStatePlayerAlive(owner);
        });
    componentCreateMap_.emplace("playerDead", [this](ActorBase& owner)
        {
            return CreateComponentStatePlayerDead(owner);
        });
    componentCreateMap_.emplace("playerHit", [this](ActorBase& owner)
        {
            return CreateComponentStatePlayerHit(owner);
        });
    componentCreateMap_.emplace("playerAttack", [this](ActorBase& owner)
        {
            return CreateComponentStatePlayerAttack(owner);
        });
    componentCreateMap_.emplace("playerRespawn", [this](ActorBase& owner)
        {
            return CreateComponentStatePlayerRespawn(owner);
        });
    componentCreateMap_.emplace("enemyAlive", [this](ActorBase& owner)
        {
            return CreateComponentStateEnemyAlive(owner);
        });
    componentCreateMap_.emplace("avilityBox", [this](ActorBase& owner)
        {
            return CreateComponentAvilityBox(owner);
        });
    componentCreateMap_.emplace("avilityShot", [this](ActorBase& owner)
        {
            return CreateComponentAvilityShot(owner);
        });
    componentCreateMap_.emplace("knockBack", [this](ActorBase& owner)
        {
            return CreateComponentKnockBack(owner);
        });
}

FactoryComponent::~FactoryComponent()
{
}