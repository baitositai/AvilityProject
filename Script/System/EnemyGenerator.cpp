#include <random>
#include "../Utility/UtilityLoad.h"
#include "../../Object/Character/Enemy/EnemyBase.h"
#include "../../Object/Character/Enemy/EnemyClone.h"
#include "../../Object/Character/Enemy/EnemyHat.h"
#include "../../Object/Character/Enemy/EnemyMushroom.h"
#include "../../Object/Character/Enemy/EnemySamurai.h"
#include "../../Object/Character/Enemy/EnemySlime.h"
#include "../../Object/Character/Enemy/EnemySnake.h"
#include "EnemyGenerator.h"

EnemyGenerator::EnemyGenerator()
{
}

EnemyGenerator::~EnemyGenerator()
{
}

void EnemyGenerator::InitParameter()
{
	// 情報の取得
	const auto jsonParameterMap = UtilityLoad::GetJsonMapArrayData("EnemiesParameter");

	// パラメータの取得
	const auto jsonCloneParameter = jsonParameterMap.at("clone").front();
	auto parameterClone = std::make_unique<ParameterEnemy>();
	parameterClone->LoadParameter(jsonCloneParameter);
	templateParameterMap_.emplace(EnemyTypes::TYPE::CLONE, std::move(parameterClone));

	const auto jsonSlimeParameter = jsonParameterMap.at("slime").front();
	auto parameterSlime = std::make_unique<ParameterEnemy>();
	parameterSlime->LoadParameter(jsonSlimeParameter);
	templateParameterMap_.emplace(EnemyTypes::TYPE::SLIME, std::move(parameterSlime));

	const auto jsonMushroomParameter = jsonParameterMap.at("mushroom").front();
	auto parameterMushroom = std::make_unique<ParameterEnemy>();
	parameterMushroom->LoadParameter(jsonMushroomParameter);
	templateParameterMap_.emplace(EnemyTypes::TYPE::MUSHROOM, std::move(parameterMushroom));

	const auto jsonHatParameter = jsonParameterMap.at("hat").front();
	auto parameterHat = std::make_unique<ParameterEnemy>();
	parameterHat->LoadParameter(jsonHatParameter);
	templateParameterMap_.emplace(EnemyTypes::TYPE::HAT, std::move(parameterHat));

	const auto jsonSnakeParameter = jsonParameterMap.at("snake").front();
	auto parameterSnake = std::make_unique<ParameterEnemy>();
	parameterSnake->LoadParameter(jsonSnakeParameter);
	templateParameterMap_.emplace(EnemyTypes::TYPE::SNAKE, std::move(parameterSnake));

	const auto jsonSamuraiParameter = jsonParameterMap.at("samurai").front();
	auto parameterSamurai = std::make_unique<ParameterEnemy>();
	parameterSamurai->LoadParameter(jsonSamuraiParameter);
	templateParameterMap_.emplace(EnemyTypes::TYPE::SAMURAI, std::move(parameterSamurai));
}

std::unordered_map<EnemyTypes::TYPE, std::vector<std::unique_ptr<EnemyBase>>> EnemyGenerator::CreateEnemyMap(const std::vector<Vector2F>& createPositionsList, const std::unordered_map<EnemyTypes::TYPE, SpawnConfig> spawnConfigMap)
{ 
	std::unordered_map<EnemyTypes::TYPE, std::vector<std::unique_ptr<EnemyBase>>> ret;
	
	for (const Vector2F& createPosition : createPositionsList)
	{
		// 一つの座標で生成する敵数をランダムで決める
	}

	// 管理マップを返す
	return ret;
}

std::unique_ptr<EnemyBase> EnemyGenerator::CreateEnemy(const EnemyTypes::TYPE type)
{
	// 必要とするものがあるか探索
	auto it = createEnemyMap_.find(type);

	// ある場合
	if (it != createEnemyMap_.end())
	{
		// 生成したものを返す
		return it->second();
	}

	// 見つからない場合空で返す
	return nullptr;
}

EnemyTypes::TYPE EnemyGenerator::LotteryEnemyType(const std::unordered_map<EnemyTypes::TYPE, EnemyGenerator::SpawnConfig>& spawnTable)
{
	// 乱数生成器の用意
	std::random_device seedGen;
	std::mt19937 engine(seedGen());

	// 確率の合計値を計算
	float totalRate = 0.0f;
	for (const auto& pair : spawnTable)
	{
		totalRate += pair.second.spawnRate;
	}

	// 0から合計値までの間で乱数を生成
	std::uniform_real_distribution<float> dist(0.0f, totalRate);
	float randomValue = dist(engine);

	// 乱数をもとに敵を抽選
	float currentRateSum = 0.0f;
	for (const auto& pair : spawnTable)
	{
		currentRateSum += pair.second.spawnRate;
		if (randomValue <= currentRateSum)
		{
			return pair.first;
		}
	}

	// 万が一外れた場合は先頭の要素を返す
	return spawnTable.begin()->first;
}

std::unique_ptr<EnemyClone> EnemyGenerator::CreateEnemyClone()
{
	return std::make_unique<EnemyClone>(std::move(*templateParameterMap_.at(EnemyTypes::TYPE::CLONE)));
}

std::unique_ptr<EnemySlime> EnemyGenerator::CreateEnemySlime()
{
	return std::make_unique<EnemySlime>(std::move(*templateParameterMap_.at(EnemyTypes::TYPE::SLIME)));
}

std::unique_ptr<EnemyMushroom> EnemyGenerator::CreateEnemyMushroom()
{
	return std::make_unique<EnemyMushroom>(std::move(*templateParameterMap_.at(EnemyTypes::TYPE::MUSHROOM)));
}

std::unique_ptr<EnemySnake> EnemyGenerator::CreateEnemySnake()
{
	return std::make_unique<EnemySnake>(std::move(*templateParameterMap_.at(EnemyTypes::TYPE::SNAKE)));
}

std::unique_ptr<EnemyHat> EnemyGenerator::CreateEnemyHat()
{
	return std::make_unique<EnemyHat>(std::move(*templateParameterMap_.at(EnemyTypes::TYPE::HAT)));
}

std::unique_ptr<EnemySamurai> EnemyGenerator::CreateEnemySamurai()
{
	return std::make_unique<EnemySamurai>(std::move(*templateParameterMap_.at(EnemyTypes::TYPE::SAMURAI)));
}