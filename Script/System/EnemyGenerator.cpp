#include <random>
#include "../../Object/Character/Enemy/EnemyBase.h"
#include "../../Object/Character/Enemy/EnemyClone.h"
#include "../../Object/Character/Enemy/EnemyHat.h"
#include "../../Object/Character/Enemy/EnemyMushroom.h"
#include "../../Object/Character/Enemy/EnemySamurai.h"
#include "../../Object/Character/Enemy/EnemySlime.h"
#include "../../Object/Character/Enemy/EnemySnake.h"
#include "../../Object/Character/Enemy/EnemyMaid.h"
#include "../Utility/UtilityLoad.h"
#include "EnemyGenerator.h"

EnemyGenerator::EnemyGenerator()
{
	// シードを用意してエンジンに渡しておく
	std::random_device seedGen;
	randomCountEngine_.seed(seedGen());

	// 生成処理の登録
	createEnemyMap_.emplace(EnemyTypes::TYPE::CLONE, [this]()
		{
			return CreateEnemyClone();
		});
	createEnemyMap_.emplace(EnemyTypes::TYPE::SLIME, [this]()
		{
			return CreateEnemySlime();
		});
	createEnemyMap_.emplace(EnemyTypes::TYPE::MUSHROOM, [this]()
		{
			return CreateEnemyMushroom();
		});
	createEnemyMap_.emplace(EnemyTypes::TYPE::HAT, [this]()
		{
			return CreateEnemyHat();
		});
	createEnemyMap_.emplace(EnemyTypes::TYPE::SNAKE, [this]()
		{
			return CreateEnemySnake();
		});
	createEnemyMap_.emplace(EnemyTypes::TYPE::SAMURAI, [this]()
		{
			return CreateEnemySamurai();
		});
	createEnemyMap_.emplace(EnemyTypes::TYPE::MAID, [this]()
		{
			return CreateEnemyMaid();
		});
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

	const auto jsonMaidParameter = jsonParameterMap.at("maid").front();
	auto parameterMaid = std::make_unique<ParameterEnemyMaid>();
	parameterMaid->LoadParameter(jsonMaidParameter);
	templateParameterMap_.emplace(EnemyTypes::TYPE::MAID, std::move(parameterMaid));
}

std::unordered_map<EnemyTypes::TYPE, std::vector<std::unique_ptr<EnemyBase>>> EnemyGenerator::CreateEnemyMap(const Parameter& parameter)
{
	std::unordered_map<EnemyTypes::TYPE, std::vector<std::unique_ptr<EnemyBase>>> ret;
	std::unordered_map<EnemyTypes::TYPE, float> enemySpawnMap;

	for (const EnemyTypes::TYPE& type : parameter.createEnemyTypeList)
	{
		const auto it = templateParameterMap_.find(type);

		if (it->second)
		{
			enemySpawnMap.emplace(type, it->second->spawnRate_);
		}
	}

	for (const Vector2F& pos : parameter.createPositionsList)
	{
		// 生成数を決める
		std::uniform_int_distribution<int> countDist(parameter.createCountMin, parameter.createCountMax);
		const int createCount = countDist(randomCountEngine_);

		for (int i = 0; i < createCount; i++)
		{
			// 生成する種類を決める
			EnemyTypes::TYPE type = LotteryEnemyType(enemySpawnMap);

			// 敵の生成
			std::unique_ptr<EnemyBase> enemy = CreateEnemy(type);
			
			// 位置調整用の値を用意
			std::uniform_real_distribution<float> offsetXDist(-parameter.createRange.x, parameter.createRange.x);
			std::uniform_real_distribution<float> offsetYDist(-parameter.createRange.y, parameter.createRange.y);
			Vector2F offset;
			offset.x = offsetXDist(randomCountEngine_);
			offset.y = offsetYDist(randomCountEngine_);

			// 敵の位置を調整
			enemy->GetParameter().pos_ = Vector2F::AddVector2F(pos, offset);

			// 敵を格納する
			ret[type].push_back(std::move(enemy));
		}
	}

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

EnemyTypes::TYPE EnemyGenerator::LotteryEnemyType(const std::unordered_map<EnemyTypes::TYPE, float>& spawnTable)
{
	// 確率の合計値を計算する
	float totalRate = 0.0f;
	for (const auto& pair : spawnTable)
	{
		totalRate += pair.second;
	}

	// 0から合計間で乱数を生成する
	std::uniform_real_distribution<float> dist(0.0f, totalRate);
	float randomValue = dist(randomCountEngine_);

	// 乱数をもとに敵を抽選する
	float currentRateSum = 0.0f;
	for (const auto& pair : spawnTable)
	{
		currentRateSum += pair.second;
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
	return std::make_unique<EnemyClone>(std::move(std::make_unique<ParameterEnemy>(*templateParameterMap_.at(EnemyTypes::TYPE::CLONE))));
}

std::unique_ptr<EnemySlime> EnemyGenerator::CreateEnemySlime()
{
	return std::make_unique<EnemySlime>(std::move(std::make_unique<ParameterEnemy>(*templateParameterMap_.at(EnemyTypes::TYPE::SLIME))));
}

std::unique_ptr<EnemyMushroom> EnemyGenerator::CreateEnemyMushroom()
{
	return std::make_unique<EnemyMushroom>(std::move(std::make_unique<ParameterEnemy>(*templateParameterMap_.at(EnemyTypes::TYPE::MUSHROOM))));
}

std::unique_ptr<EnemySnake> EnemyGenerator::CreateEnemySnake()
{
	return std::make_unique<EnemySnake>(std::move(std::make_unique<ParameterEnemy>(*templateParameterMap_.at(EnemyTypes::TYPE::SNAKE))));
}

std::unique_ptr<EnemyHat> EnemyGenerator::CreateEnemyHat()
{
	return std::make_unique<EnemyHat>(std::move(std::make_unique<ParameterEnemy>(*templateParameterMap_.at(EnemyTypes::TYPE::HAT))));
}

std::unique_ptr<EnemySamurai> EnemyGenerator::CreateEnemySamurai()
{
	return std::make_unique<EnemySamurai>(std::move(std::make_unique<ParameterEnemy>(*templateParameterMap_.at(EnemyTypes::TYPE::SAMURAI))));
}

std::unique_ptr<EnemyMaid> EnemyGenerator::CreateEnemyMaid()
{
	// メイド用のパラメータにキャスト
	auto parameterBase = templateParameterMap_.at(EnemyTypes::TYPE::MAID).get();
	auto parameterMaid = dynamic_cast<ParameterEnemyMaid*>(parameterBase);

	// 空の場合
	if (parameterMaid == nullptr)
	{
		// 空で返す
		return nullptr;
	}

	// 生成したものを返す
	auto parameter = std::make_unique<ParameterEnemyMaid>(*parameterMaid);
	return std::make_unique<EnemyMaid>(std::move(parameter));
}
