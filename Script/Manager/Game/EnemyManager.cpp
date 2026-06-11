#include <string>
#include "../../Utility/UtilityLoad.h"
#include "../../Object/Character/Enemy/EnemyBase.h"
#include "../../Object/Character/Enemy/EnemyClone.h"
#include "../../Object/Character/Enemy/EnemyMushroom.h"
#include "../../Object/Character/Enemy/EnemySlime.h"
#include "../../Object/Character/Enemy/EnemyHat.h"
#include "../../Object/Character/Enemy/EnemySnake.h"
#include "../../Object/Character/Enemy/EnemySamurai.h"
#include "../../Object/Common/Animation.h"
#include "../../System/EnemyGenerator.h"
#include "../Common/ResourceManager.h"
#include "../Manager/Game/StageManager.h"
#include "EnemyManager.h"

void EnemyManager::Init()
{
	// ‹ó‚Ìê‡–³Ž‹
	if (enemiesMap_.empty()) { return; }

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
	if (isStop_ || enemiesMap_.empty()) { return; }

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
			[](const std::unique_ptr<EnemyBase>& enemy)
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

void EnemyManager::Generator(const std::vector<Vector2F>& createPositionList)
{
	using TYPE = EnemyTypes::TYPE;

	// ¶¬—p‚Ìƒpƒ‰ƒ[ƒ^î•ñ‚ðÝ’è
	EnemyGenerator::Parameter parameter {};
	parameter.createCountMax = 2;
	parameter.createCountMin = 1;
	parameter.createPositionsList = createPositionList;
	parameter.createRange = Vector2F{ 128.0f, 64.0f };
	parameter.createEnemyTypeList = { TYPE::CLONE, TYPE::MUSHROOM, TYPE::SAMURAI, TYPE::SLIME, TYPE::SNAKE, TYPE::SLIME, TYPE::HAT };

	// ¶¬‚µ‚ÄŠi”[
	enemiesMap_ = enemyGenerator_->CreateEnemyMap(parameter);
}

void EnemyManager::Create(const EnemyTypes::TYPE type, const Vector2F& pos)
{
	// ¶¬
	auto enemy = enemyGenerator_->CreateEnemy(type);

	// ˆÊ’u’²®
	enemy->GetParameter().pos_ = pos;

	// Ši”[
	enemiesMap_[type].push_back(std::move(enemy));
}

void EnemyManager::CreateEventEnemy(const EnemyTypes::TYPE type, const Vector2F& pos)
{
	// ¶¬
	auto enemy = enemyGenerator_->CreateEnemy(type);

	// ƒCƒxƒ“ƒgŠÇ——p‚É¶ƒ|ƒCƒ“ƒ^‚Å•ÛŽ
	EnemyBase* enemyPtr = enemy.get();

	// ˆÊ’u’²®
	enemy->GetParameter().pos_ = pos;

	// ‰Šú‰»
	enemy->Init();

	// Ši”[
	enemiesMap_[type].push_back(std::move(enemy));

	// ƒCƒxƒ“ƒg‘¤‚Å‚àŠÄŽ‹‘ÎÛ‚Æ‚µ‚Ä“o˜^
	eventEnemyList_.push_back(enemyPtr);
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

const bool EnemyManager::IsBossDestroy(const EnemyTypes::TYPE type) const
{
	// ‹ó‚È‚çŒ‚”j
	return enemiesMap_.at(type).empty();
}

const bool EnemyManager::IsEmptyEventEnemies() 
{
	// Ž€–SÏ‚Ý‚Ì‚à‚Ì‚ðíœ
	eventEnemyList_.erase(
		std::remove_if(eventEnemyList_.begin(), eventEnemyList_.end(),
			[](EnemyBase* enemy) { return enemy->IsDelete(); }),
		eventEnemyList_.end()
	);

	// ‹ó‚©•Ô‚·
	return eventEnemyList_.empty();
}

EnemyManager::EnemyManager()
{
	isStop_ = false;
	enemyGenerator_ = std::make_unique<EnemyGenerator>();
	enemyGenerator_->InitParameter();
}

EnemyManager::~EnemyManager()
{
}
