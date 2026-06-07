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
	// ジェネレーターの生成
	if (!enemyGenerator_)
	{
		enemyGenerator_ = std::make_unique<EnemyGenerator>();
		enemyGenerator_->InitParameter();
	}

	// デバッグ用
	//auto enemy = enemyGenerator_->CreateEnemy(EnemyTypes::TYPE::SLIME);
	//enemy->GetParameter().pos_ = StageManager::GetInstance().GetEnemyAreaPositions().front();
	//enemiesMap_[EnemyTypes::TYPE::SLIME].push_back(std::move(enemy));

	// 空の場合後の処理を無視
	if (enemiesMap_.empty()) { return; }

	// 初期化
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

	// 更新処理
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

	// 描画処理
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

	// 初期化
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

	// 生成用のパラメータ情報を設定
	EnemyGenerator::Parameter parameter {};
	parameter.createCountMax = 2;
	parameter.createCountMin = 1;
	parameter.createPositionsList = createPositionList;
	parameter.createRange = Vector2F{ 128.0f, 64.0f };
	parameter.createEnemyTypeList = { TYPE::CLONE, TYPE::MUSHROOM, TYPE::SAMURAI, TYPE::SLIME, TYPE::SNAKE, TYPE::SLIME, TYPE::HAT };

	// 生成して格納
	enemiesMap_ = enemyGenerator_->CreateEnemyMap(parameter);

	// 初期化処理
	Init();
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
	enemyGenerator_ = nullptr;
}

EnemyManager::~EnemyManager()
{
}
