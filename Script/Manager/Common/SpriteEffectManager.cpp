#include "../../Object/Effect/EffectBase.h"
#include "SpriteEffectManager.h"

void SpriteEffectManager::Init()
{
	for (EffectBase& effect : effectList_)
	{
		effect.Init();
	}
}

void SpriteEffectManager::Update()
{
	for (EffectBase& effect : effectList_)
	{
		effect.Update();
	}
}

void SpriteEffectManager::Draw()
{
	for (EffectBase& effect : effectList_)
	{
		effect.Draw();
	}
}

void SpriteEffectManager::Add(std::unique_ptr<EffectBase> effect)
{
	// 初期化
	effect->Init();

	// 追加
	effectList_.emplace_back(std::move(effect));
}

void SpriteEffectManager::Clear()
{
	effectList_.clear();
}

void SpriteEffectManager::Sweep()
{
	// 終了したエフェクトを並び変える
	auto it = std::remove_if(effectList_.begin(), effectList_.end(),
		[](const EffectBase& effect)
		{
			return effect.IsDelete();
		});

	// 終了したエフェクトを削除する
	effectList_.erase(it, effectList_.end());
}

SpriteEffectManager::SpriteEffectManager()
{
}

SpriteEffectManager::~SpriteEffectManager()
{
}