#include "../../Component/ComponentBase.h"
#include "../../Component/ComponentMove.h"
#include "../../Component/ComponentSpriteAnimation.h"
#include "../../Component/ComponentGravity.h"
#include "../../Component/ComponentInvincible.h"
#include "../../Component/ComponentKnockBack.h"
#include "../../Component/ComponentJump.h"
#include "../../Component/ComponentCameraRangeCheck.h"
#include "../../Component/ComponentDebugCreateItemAvility.h"

#include "../../Component/Avility/ComponentAvilityBase.h"
#include "../../Component/Avility/ComponentAvilityBox.h"
#include "../../Component/Avility/ComponentAvilityShot.h"
#include "../../Component/Avility/ComponentAvilityAirwalk.h"
#include "../../Component/Avility/ComponentAvilityGravity.h"
#include "../../Component/Avility/ComponentAvilityMetal.h"
#include "../../Component/Avility/ComponentAvilitySuperman.h"
#include "../../Component/Avility/ComponentAvilityStamp.h"
#include "../../Component/Avility/ComponentAvilityAirslash.h"
#include "../../Component/Avility/ComponentAvilityTeleport.h"
#include "../../Component/Avility/ComponentAvilityGiant.h"

#include "../../Component/State/ComponentStatePlayerProcess.h"
#include "../../Component/State/ComponentStateEnemyAlive.h"
#include "../../Component/State/ComponentStateAttackDefault.h"
#include "../../Component/State/ComponentStatePlayerDead.h"
#include "../../Component/State/ComponentStateEnemyDead.h"
#include "../../Component/State/ComponentStateIdle.h"
#include "../../Component/State/ComponentStateEnter.h"
#include "../../Component/State/ComponentStatePlayerSpawn.h"
#include "../../Component/State/ComponentStatePlayerAttack.h"
#include "../../Component/State/ComponentStateDummy.h"

#include "../../Component/Logic/ComponentLogicBase.h"
#include "../../Component/Logic/ComponentLogicPatrol.h"
#include "../../Component/Logic/ComponentLogicBambooThrowing.h"
#include "../../Component/Logic/ComponentLogicBambooGrowing.h"
#include "../../Component/Logic/ComponentLogicPandaShot.h"
#include "../../Component/Logic/ComponentLogicMaid.h"

#include "../../Object/Character/CharacterBase.h" 
#include "../../Object/Character/Player.h" 
#include "../../Object/Character/Enemy/EnemyBase.h" 
#include "../../Object/Character/Enemy/EnemyPanda.h" 
#include "../../Object/Character/Enemy/EnemyMaid.h" 
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

std::unique_ptr<ComponentAvilityBase> FactoryComponent::CreateComponentAvility(const std::string& name, ActorBase& owner)
{
    // 必要とするものがあるか探索
    auto it = componentCreateMap_.find(name);

    // ある場合
    if (it != componentCreateMap_.end())
    {   
		// 生成したものをアビリティ用の型にキャストして返す
		auto avilityComponent = dynamic_cast<ComponentAvilityBase*>(it->second(owner).release());

		if (avilityComponent)
		{
			return std::unique_ptr<ComponentAvilityBase>(avilityComponent);
		}
    }

    // 見つからない場合空で返す
    return nullptr;
}

std::unique_ptr<ComponentLogicBase> FactoryComponent::CreateComponentLogicBase(const std::string& name, ActorBase& owner)
{
    // 必要とするものがあるか探索
    auto it = componentCreateMap_.find(name);

    // ある場合
    if (it != componentCreateMap_.end())
    {
        // 生成したものをアビリティ用の型にキャストして返す
        auto logicComponent = dynamic_cast<ComponentLogicBase*>(it->second(owner).release());

        if (logicComponent)
        {
            return std::unique_ptr<ComponentLogicBase>(logicComponent);
        }
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

std::unique_ptr<ComponentStatePlayerProcess> FactoryComponent::CreateComponentStatePlayerProcess(ActorBase& owner)
{
    auto* playerPtr = dynamic_cast<Player*>(&owner);

    if (playerPtr == nullptr)
    {
        // キャストに失敗した場合nullptrを返す
        return nullptr;
    }
    return std::make_unique<ComponentStatePlayerProcess>(*playerPtr);
}

std::unique_ptr<ComponentStateAttackDefault> FactoryComponent::CreateComponentStateAttackDefault(ActorBase& owner)
{
    auto* charaPtr = dynamic_cast<CharacterBase*>(&owner);

    if (charaPtr == nullptr)
    {
        // キャストに失敗した場合nullptrを返す
        return nullptr;
    }
    return std::make_unique<ComponentStateAttackDefault>(*charaPtr);
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

std::unique_ptr<ComponentAvilityStamp> FactoryComponent::CreateComponentAvilityStamp(ActorBase& owner)
{
    auto* playerPtr = dynamic_cast<Player*>(&owner);

    if (playerPtr == nullptr)
    {
        // キャストに失敗した場合nullptrを返す
        return nullptr;
    }
    return std::make_unique<ComponentAvilityStamp>(*playerPtr);
}

std::unique_ptr<ComponentAvilityAirwalk> FactoryComponent::CreateComponentAvilityAirwalk(ActorBase& owner)
{
    auto* playerPtr = dynamic_cast<Player*>(&owner);

    if (playerPtr == nullptr)
    {
        // キャストに失敗した場合nullptrを返す
        return nullptr;
    }
    return std::make_unique<ComponentAvilityAirwalk>(*playerPtr);
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

std::unique_ptr<ComponentAvilityGravity> FactoryComponent::CreateComponentAvilityGravity(ActorBase& owner)
{
    auto* playerPtr = dynamic_cast<Player*>(&owner);

    if (playerPtr == nullptr)
    {
        // キャストに失敗した場合nullptrを返す
        return nullptr;
    }
    return std::make_unique<ComponentAvilityGravity>(*playerPtr);
}

std::unique_ptr<ComponentAvilityMetal> FactoryComponent::CreateComponentAvilityMetal(ActorBase& owner)
{
    auto* playerPtr = dynamic_cast<Player*>(&owner);

    if (playerPtr == nullptr)
    {
        // キャストに失敗した場合nullptrを返す
        return nullptr;
    }
    return std::make_unique<ComponentAvilityMetal>(*playerPtr);
}

std::unique_ptr<ComponentAvilitySuperman> FactoryComponent::CreateComponentAvilitySuperman(ActorBase& owner)
{
    auto* playerPtr = dynamic_cast<Player*>(&owner);

    if (playerPtr == nullptr)
    {
        // キャストに失敗した場合nullptrを返す
        return nullptr;
    }
    return std::make_unique<ComponentAvilitySuperman>(*playerPtr);
}

std::unique_ptr<ComponentAvilityAirslash> FactoryComponent::CreateComponentAvilityAirslash(ActorBase& owner)
{
    auto* playerPtr = dynamic_cast<Player*>(&owner);

    if (playerPtr == nullptr)
    {
        // キャストに失敗した場合nullptrを返す
        return nullptr;
    }
    return std::make_unique<ComponentAvilityAirslash>(*playerPtr);
}

std::unique_ptr<ComponentAvilityTeleport> FactoryComponent::CreateComponentAvilityTeleport(ActorBase& owner)
{
    auto* playerPtr = dynamic_cast<Player*>(&owner);

    if (playerPtr == nullptr)
    {
        // キャストに失敗した場合nullptrを返す
        return nullptr;
    }
    return std::make_unique<ComponentAvilityTeleport>(*playerPtr);
}

std::unique_ptr<ComponentAvilityGiant> FactoryComponent::CreateComponentAvilityGiant(ActorBase& owner)
{
    auto* playerPtr = dynamic_cast<Player*>(&owner);

    if (playerPtr == nullptr)
    {
        // キャストに失敗した場合nullptrを返す
        return nullptr;
    }
    return std::make_unique<ComponentAvilityGiant>(*playerPtr);
}

std::unique_ptr<ComponentLogicPatrol> FactoryComponent::CreateComponentLogicPatrol(ActorBase& owner)
{
    auto* enemyPtr = dynamic_cast<EnemyBase*>(&owner);

    if (enemyPtr == nullptr)
    {
        // キャストに失敗した場合nullptrを返す
        return nullptr;
    }
    return std::make_unique<ComponentLogicPatrol>(*enemyPtr);
}

std::unique_ptr<ComponentLogicBambooThrowing> FactoryComponent::CreateComponentLogicBambooThrowing(ActorBase& owner)
{
    auto* enemyPtr = dynamic_cast<EnemyPanda*>(&owner);

    if (enemyPtr == nullptr)
    {
        // キャストに失敗した場合nullptrを返す
        return nullptr;
    }
    return std::make_unique<ComponentLogicBambooThrowing>(*enemyPtr);
}

std::unique_ptr<ComponentLogicBambooGrowing> FactoryComponent::CreateComponentLogicBambooGrowing(ActorBase& owner)
{
    auto* enemyPtr = dynamic_cast<EnemyPanda*>(&owner);

    if (enemyPtr == nullptr)
    {
        // キャストに失敗した場合nullptrを返す
        return nullptr;
    }
    return std::make_unique<ComponentLogicBambooGrowing>(*enemyPtr);
}

std::unique_ptr<ComponentLogicPandaShot> FactoryComponent::CreateComponentLogicPandaShot(ActorBase& owner)
{
    auto* enemyPtr = dynamic_cast<EnemyPanda*>(&owner);

    if (enemyPtr == nullptr)
    {
        // キャストに失敗した場合nullptrを返す
        return nullptr;
    }
    return std::make_unique<ComponentLogicPandaShot>(*enemyPtr);
}

std::unique_ptr<ComponentLogicMaid> FactoryComponent::CreateComponentLogicMaid(ActorBase& owner)
{
    auto* enemyPtr = dynamic_cast<EnemyMaid*>(&owner);

    if (enemyPtr == nullptr)
    {
        // キャストに失敗した場合nullptrを返す
        return nullptr;
    }
    return std::make_unique<ComponentLogicMaid>(*enemyPtr);
}

std::unique_ptr<ComponentKnockBack> FactoryComponent::CreateComponentKnockBack(ActorBase& owner)
{
    return std::make_unique<ComponentKnockBack>(owner);
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

std::unique_ptr<ComponentStateEnter> FactoryComponent::CreateComponentStateEnter(ActorBase& owner)
{
    auto* charaPtr = dynamic_cast<CharacterBase*>(&owner);

    if (charaPtr == nullptr)
    {
        // キャストに失敗した場合nullptrを返す
        return nullptr;
    }
    return std::make_unique<ComponentStateEnter>(*charaPtr);
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

std::unique_ptr<ComponentStateEnemyDead> FactoryComponent::CreateComponentStateEnemyDead(ActorBase& owner)
{
    auto* enemyPtr = dynamic_cast<EnemyBase*>(&owner);

    if (enemyPtr == nullptr)
    {
        // キャストに失敗した場合nullptrを返す
        return nullptr;
    }
    return std::make_unique<ComponentStateEnemyDead>(*enemyPtr);
}

std::unique_ptr<ComponentStateEnemyAlive> FactoryComponent::CreateComponentStateEnemyAlive(ActorBase& owner)
{
    auto* enemyPtr = dynamic_cast<EnemyBase*>(&owner);

    if (enemyPtr == nullptr)
    {
        // キャストに失敗した場合nullptrを返す
        return nullptr;
    }
    return std::make_unique<ComponentStateEnemyAlive>(*enemyPtr);
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

std::unique_ptr<ComponentStatePlayerSpawn> FactoryComponent::CreateComponentStatePlayerSpawn(ActorBase& owner)
{
    auto* playerPtr = dynamic_cast<Player*>(&owner);

    if (playerPtr == nullptr)
    {
        // キャストに失敗した場合nullptrを返す
        return nullptr;
    }
    return std::make_unique<ComponentStatePlayerSpawn>(*playerPtr);
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

std::unique_ptr<ComponentCameraRangeCheck> FactoryComponent::CreateComponentCameraRangeCheck(ActorBase& owner)
{
    auto* playerPtr = dynamic_cast<Player*>(&owner);

    if (playerPtr == nullptr)
    {
        // キャストに失敗した場合nullptrを返す
        return nullptr;
    }
    return std::make_unique<ComponentCameraRangeCheck>(*playerPtr);
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

std::unique_ptr<ComponentDebugCreateItemAvility> FactoryComponent::CreateComponentDebugCreateItemAvility(ActorBase& owner)
{
    auto* playerPtr = dynamic_cast<Player*>(&owner);

    if (playerPtr == nullptr)
    {
        // キャストに失敗した場合nullptrを返す
        return nullptr;
    }
    return std::make_unique<ComponentDebugCreateItemAvility>(*playerPtr);
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
    componentCreateMap_.emplace("playerProcess", [this](ActorBase& owner)
        {
            return CreateComponentStatePlayerProcess(owner);
        });
    componentCreateMap_.emplace("attackDefault", [this](ActorBase& owner)
        {
            return CreateComponentStateAttackDefault(owner);
        });
    componentCreateMap_.emplace("box", [this](ActorBase& owner)
        {
            return CreateComponentAvilityBox(owner);
        });
    componentCreateMap_.emplace("stamp", [this](ActorBase& owner)
        {
            return CreateComponentAvilityStamp(owner);
        });
    componentCreateMap_.emplace("gravityControll", [this](ActorBase& owner)
        {
            return CreateComponentAvilityGravity(owner);
        });
    componentCreateMap_.emplace("shot", [this](ActorBase& owner)
        {
            return CreateComponentAvilityShot(owner);
        });
    componentCreateMap_.emplace("metal", [this](ActorBase& owner)
        {
            return CreateComponentAvilityMetal(owner);
        });
    componentCreateMap_.emplace("airslash", [this](ActorBase& owner)
        {
            return CreateComponentAvilityAirslash(owner);
        });
    componentCreateMap_.emplace("superman", [this](ActorBase& owner)
        {
            return CreateComponentAvilitySuperman(owner);
        });
    componentCreateMap_.emplace("teleport", [this](ActorBase& owner)
        {
            return CreateComponentAvilityTeleport(owner);
        });
    componentCreateMap_.emplace("giant", [this](ActorBase& owner)
        {
            return CreateComponentAvilityGiant(owner);
        });
    componentCreateMap_.emplace("airwalk", [this](ActorBase& owner)
        {
            return CreateComponentAvilityAirwalk(owner);
        });
    componentCreateMap_.emplace("knockBack", [this](ActorBase& owner)
        {
            return CreateComponentKnockBack(owner);
        });
    componentCreateMap_.emplace("idle", [this](ActorBase& owner)
        {
            return CreateComponentStateIdle(owner);
        });
    componentCreateMap_.emplace("enter", [this](ActorBase& owner)
        {
            return CreateComponentStateEnter(owner);
        });
    componentCreateMap_.emplace("playerDead", [this](ActorBase& owner)
        {
            return CreateComponentStatePlayerDead(owner);
        });
    componentCreateMap_.emplace("enemyDead", [this](ActorBase& owner)
        {
            return CreateComponentStateEnemyDead(owner);
        });
    componentCreateMap_.emplace("enemyAlive", [this](ActorBase& owner)
        {
            return CreateComponentStateEnemyAlive(owner);
        });
    componentCreateMap_.emplace("spawn", [this](ActorBase& owner)
        {
            return CreateComponentStatePlayerSpawn(owner);
        });
    componentCreateMap_.emplace("playerAttack", [this](ActorBase& owner)
        {
            return CreateComponentStatePlayerAttack(owner);
        });
    componentCreateMap_.emplace("dummy", [this](ActorBase& owner)
        {
            return CreateComponentStateDummy(owner);
        });
    componentCreateMap_.emplace("jump", [this](ActorBase& owner)
        {
            return CreateComponentJump(owner);
        });
    componentCreateMap_.emplace("patrol", [this](ActorBase& owner)
        {
            return CreateComponentLogicPatrol(owner);
        });
    componentCreateMap_.emplace("bambooThrowing", [this](ActorBase& owner)
        {
            return CreateComponentLogicBambooThrowing(owner);
        });
    componentCreateMap_.emplace("bambooGrowing", [this](ActorBase& owner)
        {
            return CreateComponentLogicBambooGrowing(owner);
        });
    componentCreateMap_.emplace("pandaShot", [this](ActorBase& owner)
        {
            return CreateComponentLogicPandaShot(owner);
        });
    componentCreateMap_.emplace("maid", [this](ActorBase& owner)
        {
            return CreateComponentLogicMaid(owner);
        });
    componentCreateMap_.emplace("debugCreateItemAvility", [this](ActorBase& owner)
        {
            return CreateComponentDebugCreateItemAvility(owner);
        });
    componentCreateMap_.emplace("cameraRangeCheck", [this](ActorBase& owner)
        {
            return CreateComponentCameraRangeCheck(owner);
        });
}

FactoryComponent::~FactoryComponent()
{
}