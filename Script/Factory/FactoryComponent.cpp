#include "../../Component/ComponentBase.h"
#include "../../Component/ComponentMove.h"
#include "../../Component/ComponentSpriteAnimation.h"
#include "../../Component/Action/ComponentActionPlayer.h"
#include "../../Object/Character/CharacterBase.h" 
#include "../../Object/Character/Player.h" 
#include "../../Object/ActorBase.h" 
#include "FactoryComponent.h"

FactoryComponent::FactoryComponent()
{
    // ê∂ê¨èàóùÇÃìoò^
    componentCreateMap_.emplace("move", [this](ActorBase& owner)
        {
            return CreateComponentMove(owner);
        });
    componentCreateMap_.emplace("spriteAnimation", [this](ActorBase& owner)
        {
            return CreateComponentSpriteAnimation(owner);
        });
    componentCreateMap_.emplace("actionPlayer", [this](ActorBase& owner)
        {
            return CreateComponentActionPlayer(owner);
        });
}

FactoryComponent::~FactoryComponent()
{
}

std::unique_ptr<ComponentBase> FactoryComponent::CreateComponent(const std::string& name, ActorBase& owner)
{
    // ïKóvÇ∆Ç∑ÇÈÇ‡ÇÃÇ™Ç†ÇÈÇ©íTçı
    auto it = componentCreateMap_.find(name);

    // Ç†ÇÈèÍçá
    if (it != componentCreateMap_.end())
    {
        // ê∂ê¨ÇµÇΩÇ‡ÇÃÇï‘Ç∑
        return it->second(owner);
    }

    // å©Ç¬Ç©ÇÁÇ»Ç¢èÍçáãÛÇ≈ï‘Ç∑
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

std::unique_ptr<ComponentActionPlayer> FactoryComponent::CreateComponentActionPlayer(ActorBase& owner)
{
    auto* characterPtr = dynamic_cast<CharacterBase*>(&owner);

    if (characterPtr == nullptr)
    {
        // ÉLÉÉÉXÉgÇ…é∏îsÇµÇΩèÍçánullptrÇï‘Ç∑
        return nullptr;
    }

    return std::make_unique<ComponentActionPlayer>(*characterPtr);

}