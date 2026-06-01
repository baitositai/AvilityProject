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
#include "../Common/ResourceManager.h"
#include "EnemyManager.h"

void EnemyManager::Init()
{
	// パラメータの初期化
	InitParameter();

	// 1. クローン用の生成：最初から派生クラスの unique_ptr として生成する
	//auto parameterClone = std::make_unique<ParameterEnemyClone>(*templateParameterMap_.at(TYPE::CLONE));

	//std::vector<std::unique_ptr<EnemyClone>> cloneEnemies;
	//// std::make_unique の戻り値はそのまま move で渡せる
	//cloneEnemies.push_back(std::make_unique<EnemyClone>(std::move(parameterClone)));
	//enemiesMap_.emplace(TYPE::CLONE, std::move(cloneEnemies));

	// 2. マッシュルーム用の生成：パラメータの unique_ptr をそのままコンストラクタに move する
	std::vector<std::unique_ptr<EnemyBase>> mushroomEnemies;
	auto parameterMushroom = std::make_unique<ParameterEnemy>(*templateParameterMap_.at(TYPE::MUSHROOM));
	mushroomEnemies.push_back(std::make_unique<EnemyMushroom>(std::move(parameterMushroom)));
	enemiesMap_.emplace(TYPE::MUSHROOM, std::move(mushroomEnemies));

	// 3. ハット用の生成
	std::vector<std::unique_ptr<EnemyBase>> hatEnemies;
	auto parameterHat = std::make_unique<ParameterEnemy>(*templateParameterMap_.at(TYPE::HAT));
	hatEnemies.push_back(std::make_unique<EnemyHat>(std::move(parameterHat)));
	enemiesMap_.emplace(TYPE::HAT, std::move(hatEnemies));

	// 4. スネーク用の生成
	std::vector<std::unique_ptr<EnemyBase>> snakeEnemies;
	auto parameterSnake = std::make_unique<ParameterEnemy>(*templateParameterMap_.at(TYPE::SNAKE));
	snakeEnemies.push_back(std::make_unique<EnemySnake>(std::move(parameterSnake)));
	enemiesMap_.emplace(TYPE::SNAKE, std::move(snakeEnemies));

	// 5. スライム用の生成
	std::vector<std::unique_ptr<EnemyBase>> slimeEnemies;
	auto parameterSlime = std::make_unique<ParameterEnemy>(*templateParameterMap_.at(TYPE::SLIME));
	slimeEnemies.push_back(std::make_unique<EnemySlime>(std::move(parameterSlime)));
	enemiesMap_.emplace(TYPE::SLIME, std::move(slimeEnemies));

	// 6. サムライ用の生成
	std::vector<std::unique_ptr<EnemyBase>> samuraiEnemies;
	auto parameterSamurai = std::make_unique<ParameterEnemy>(*templateParameterMap_.at(TYPE::SAMURAI));
	samuraiEnemies.push_back(std::make_unique<EnemySamurai>(std::move(parameterSamurai)));
	enemiesMap_.emplace(TYPE::SAMURAI, std::move(samuraiEnemies));

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

void EnemyManager::InitParameter()
{
	// 情報の取得
	const auto jsonParameterMap = UtilityLoad::GetJsonMapArrayData("EnemiesParameter");

	// パラメータの取得
	const auto jsonCloneParameter = jsonParameterMap.at("clone").front();
	auto parameterClone = std::make_unique<ParameterEnemyClone>();
	parameterClone->LoadParameter(jsonCloneParameter);
	templateParameterMap_.emplace(TYPE::CLONE, std::move(parameterClone));

	const auto jsonSlimeParameter = jsonParameterMap.at("slime").front();
	auto parameterSlime = std::make_unique<ParameterEnemy>();
	parameterSlime->LoadParameter(jsonSlimeParameter);
	templateParameterMap_.emplace(TYPE::SLIME, std::move(parameterSlime));

	const auto jsonMushroomParameter = jsonParameterMap.at("mushroom").front();
	auto parameterMushroom = std::make_unique<ParameterEnemy>();
	parameterMushroom->LoadParameter(jsonMushroomParameter);
	templateParameterMap_.emplace(TYPE::MUSHROOM, std::move(parameterMushroom));

	const auto jsonHatParameter = jsonParameterMap.at("hat").front();
	auto parameterHat = std::make_unique<ParameterEnemy>();
	parameterHat->LoadParameter(jsonHatParameter);
	templateParameterMap_.emplace(TYPE::HAT, std::move(parameterHat));

	const auto jsonSnakeParameter = jsonParameterMap.at("snake").front();
	auto parameterSnake = std::make_unique<ParameterEnemy>();
	parameterSnake->LoadParameter(jsonSnakeParameter);
	templateParameterMap_.emplace(TYPE::SNAKE, std::move(parameterSnake));

	const auto jsonSamuraiParameter = jsonParameterMap.at("samurai").front();
	auto parameterSamurai = std::make_unique<ParameterEnemy>();
	parameterSamurai->LoadParameter(jsonSamuraiParameter);
	templateParameterMap_.emplace(TYPE::SAMURAI, std::move(parameterSamurai));
}

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
}
