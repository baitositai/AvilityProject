#include <string>
#include "../../Utility/UtilityLoad.h"
#include "../../Object/Character/CharacterBase.h"
#include "../../Object/Character/Enemy/EnemyClone.h"
#include "../../Object/Common/Animation.h"
#include "../Common/ResourceManager.h"
#include "EnemyManager.h"

void EnemyManager::Init()
{
	// î•ñ‚Ìæ“¾
	const auto jsonParameterMap = UtilityLoad::GetJsonMapArrayData("EnemiesParameter");
	const auto jsonParameter = jsonParameterMap.at("clone").front();

	// ƒpƒ‰ƒ[ƒ^‚Ìæ“¾
	auto parameter = std::make_unique<ParameterEnemyClone>();
	parameter->LoadParameter(jsonParameter);
	parameter->pos_ = { 600, 1800 };

	// ”z—ñ‚ÉŠi”[
	std::vector<std::unique_ptr<CharacterBase>> enemies;
	enemies.push_back(std::move(std::make_unique<EnemyClone>(std::move(parameter))));

	// ƒ}ƒbƒv‚ÉŠi”[
	enemiesMap_.emplace(TYPE::CLONE, std::move(enemies));

	// ‰Šú‰»
	for (const auto& enemiesList : enemiesMap_)
	{
		for (const auto& enemy : enemiesList.second)
		{
			enemy->Init();
		}
	}
}

void EnemyManager::Update()
{
	if (enemiesMap_.empty()) { return; }

	// XVˆ—
	for (auto& enemiesList : enemiesMap_)
	{
		for (auto& enemy : enemiesList.second)
		{
			enemy->Update();
		}
	}
}

void EnemyManager::Draw()
{
	if (enemiesMap_.empty()) { return; }

	// •`‰æˆ—
	for (auto& enemiesList : enemiesMap_)
	{
		for (auto& enemy : enemiesList.second)
		{
			enemy->Draw();
		}
	}
}

void EnemyManager::Sweep()
{
	for (auto& enemiesList : enemiesMap_)
	{
		auto it = std::remove_if(enemiesList.second.begin(), enemiesList.second.end(),
			[](const std::unique_ptr<CharacterBase>& enemy)
			{
				if (enemy == nullptr)
				{
					return true;
				}
				return enemy->IsDelete();
			});
		enemiesList.second.erase(it, enemiesList.second.end());
	}
}

void EnemyManager::DebugDraw()
{
	if (enemiesMap_.empty()) { return; }

	// ‰Šú‰»
	for (auto& enemiesList : enemiesMap_)
	{
		for (auto& enemy : enemiesList.second)
		{
			enemy->DebugDraw();
		}
	}
}

void EnemyManager::Clear()
{
	if (enemiesMap_.empty())
	{
		return;
	}

	for (auto& enemiesList : enemiesMap_)
	{
		for (auto& enemy : enemiesList.second)
		{
			if (enemy == nullptr)
			{
				continue;
			}
			enemy->Delete();
			enemy.reset();
		}
		enemiesList.second.clear();
	}
	enemiesMap_.clear();
}

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
}
