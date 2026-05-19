#include "../../Object/ActorBase.h"
#include "../../Object/Effect/EffectBase.h"
#include "SpriteEffectManager.h"

void SpriteEffectManager::Init()
{
	for (auto& effect : effectList_)
	{
		effect->Init();
	}
}

void SpriteEffectManager::Update()
{
	for (auto& effect : effectList_)
	{
		effect->Update();
	}
}

void SpriteEffectManager::Draw()
{
	for (auto& effect : effectList_)
	{
		effect->Draw();
	}
}

void SpriteEffectManager::Add(std::unique_ptr<EffectBase> effect)
{
	// ‰Šú‰»
	effect->Init();

	// ’Ç‰Á
	effectList_.emplace_back(std::move(effect));
}

void SpriteEffectManager::Clear()
{
	effectList_.clear();
}

void SpriteEffectManager::Sweep()
{
	auto it = std::remove_if(effectList_.begin(), effectList_.end(),
		[](const std::unique_ptr<EffectBase>& effect)
		{
			return effect->IsDelete();
		});

	effectList_.erase(it, effectList_.end());
}

SpriteEffectManager::SpriteEffectManager()
{
}

SpriteEffectManager::~SpriteEffectManager()
{
}