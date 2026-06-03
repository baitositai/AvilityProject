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

std::unordered_map<EnemyTypes::TYPE, std::vector<std::unique_ptr<EnemyBase>>> EnemyGenerator::CreateEnemyMap(const std::vector<Vector2F>& CreatePositionsList)
{
	return std::unordered_map<EnemyTypes::TYPE, std::vector<std::unique_ptr<EnemyBase>>>();
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
