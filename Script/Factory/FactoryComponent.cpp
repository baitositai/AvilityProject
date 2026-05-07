#include "../../Component/ComponentBase.h"
#include "../../Component/ComponentMove.h"
#include "../../Component/ComponentSpriteAnimation.h"
#include "../../Component/ComponentGravity.h"
#include "../../Component/ComponentInvincible.h"
#include "../../Component/ComponentKnockBack.h"
#include "../../Component/ComponentJump.h"
#include "../../Component/Avility/ComponentAvilityBox.h"
#include "../../Component/Avility/ComponentAvilityShot.h"
#include "../../Component/Avility/ComponentAvilityChargeShot.h"
#include "../../Component/State/Player/ComponentStatePlayerAttack.h"
#include "../../Component/State/Player/ComponentStatePlayerAlive.h"
#include "../../Component/State/ComponentStateDead.h"
#include "../../Component/State/ComponentStateIdle.h"
#include "../../Component/State/ComponentStateDummy.h"co
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

std::unique_ptr<ComponentStateIdle> FactoryComponent::CreateComponentStateIdle(ActorBase& owner)
{
    auto* charaPtr = dynamic_cast<CharacterBase*>(&owner);

    if (charaPtr == nullptr)
    {
        // キャストに失敗した場合nullptrを返す
        return nullptr;
    }
    return std::make_unique<ComponentStateIdle>(*charaPtr);
}

std::unique_ptr<ComponentStateDead> FactoryComponent::CreateComponentStateDead(ActorBase& owner)
{
    auto* charaPtr = dynamic_cast<CharacterBase*>(&owner);

    if (charaPtr == nullptr)
    {
        // キャストに失敗した場合nullptrを返す
        return nullptr;
    }
    return std::make_unique<ComponentStateDead>(*charaPtr);
}

std::unique_ptr<ComponentStateDummy> FactoryComponent::CreateComponentStateDummy(ActorBase& owner)
{
    auto* charaPtr = dynamic_cast<CharacterBase*>(&owner);

    if (charaPtr == nullptr)
    {
        // キャストに失敗した場合nullptrを返す
        return nullptr;
    }
    return std::make_unique<ComponentStateDummy>(*charaPtr);
}

std::unique_ptr<ComponentInvincible> FactoryComponent::CreateComponentInvincible(ActorBase& owner)
{
    auto* charaPtr = dynamic_cast<CharacterBase*>(&owner);

    if (charaPtr == nullptr)
    {
        // キャストに失敗した場合nullptrを返す
        return nullptr;
    }
    return std::make_unique<ComponentInvincible>(*charaPtr);
}

std::unique_ptr<ComponentJump> FactoryComponent::CreateComponentJump(ActorBase& owner)
{
    auto* charaPtr = dynamic_cast<CharacterBase*>(&owner);

    if (charaPtr == nullptr)
    {
        // キャストに失敗した場合nullptrを返す
        return nullptr;
    }
    return std::make_unique<ComponentJump>(*charaPtr);
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
    componentCreateMap_.emplace("invincible", [this](ActorBase& owner)
        {
            return CreateComponentInvincible(owner);
        });
    componentCreateMap_.emplace("playerAlive", [this](ActorBase& owner)
        {
            return CreateComponentStatePlayerAlive(owner);
        });
    componentCreateMap_.emplace("playerAttack", [this](ActorBase& owner)
        {
            return CreateComponentStatePlayerAttack(owner);
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
    componentCreateMap_.emplace("idle", [this](ActorBase& owner)
        {
            return CreateComponentStateIdle(owner);
        });
    componentCreateMap_.emplace("dead", [this](ActorBase& owner)
        {
            return CreateComponentStateDead(owner);
        });
    componentCreateMap_.emplace("dummy", [this](ActorBase& owner)
        {
            return CreateComponentStateDummy(owner);
        });
    componentCreateMap_.emplace("jump", [this](ActorBase& owner)
        {
            return CreateComponentJump(owner);
        });
}

FactoryComponent::~FactoryComponent()
{
}