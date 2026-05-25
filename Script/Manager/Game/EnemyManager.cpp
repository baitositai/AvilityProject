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
	// I—¹‚µ‚½“G‚ğ•À‚Ñ•Ï‚¦‚é
	for (auto& enemiesList : enemiesMap_)
	{
		auto it = std::remove_if(enemiesList.second.begin(), enemiesList.second.end(),
			[](const std::unique_ptr<CharacterBase>& enemy)
			{
				return enemy->IsDelete();
			});
		enemiesList.second.erase(it, enemiesList.second.end());
	}
}

void EnemyManager::DebugDraw()
{
	// ‰Šú‰»
	for (auto& enemiesList : enemiesMap_)
	{
		for (auto& enemy : enemiesList.second)
		{
			enemy->DebugDraw();
		}
	}
}

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
}
