#include "FactoryComponent.h"

FactoryComponent::FactoryComponent()
{
    // ¶¬ˆ—‚Ì“o˜^
    componentCreateMap_.emplace("spriteAnimation", std::bind(&FactoryComponent::CreateComponentSpriteAnimation(), this));
    componentCreateMap_.emplace("actionPlayer", std::bind(&FactoryComponent::CreateComponentActionPlayer(), this));
}

FactoryComponent::~FactoryComponent()
{
}

std::unique_ptr<ComponentBase> FactoryComponent::CreateComponent(const std::string& name)
{
    // •K—v‚Æ‚·‚é‚à‚Ì‚ª‚ ‚é‚©’Tõ
    auto it = componentCreateMap_.find(name);

    // ‚ ‚éê‡
    if (it != componentCreateMap_.end())
    {
        // ¶¬‚µ‚½‚à‚Ì‚ğ•Ô‚·
        return it->second();
    }

    // Œ©‚Â‚©‚ç‚È‚¢ê‡‹ó‚Å•Ô‚·
    return nullptr;
}

std::unique_ptr<ComponentSpriteAnimation> FactoryComponent::CreateComponentSpriteAnimation()
{
    return std::make_unique<ComponentSpriteAnimation>();
}

std::unique_ptr<ComponentActionPlayer> FactoryComponent::CreateComponentActionPlayer()
{
    return std::make_unique<ComponentActionPlayer>();
}