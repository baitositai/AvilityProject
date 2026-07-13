#include "../Utility/UtilityLoad.h"
#include "../Object/Gimmick/GimmickDoor.h"
#include "../Object/Gimmick/GimmickTarget.h"
#include "../Object/Gimmick/GimmickBamboo.h"
#include "../Object/Gimmick/GimmickGrowingBamboo.h"
#include "../Object/Gimmick/GimmickTreasureChest.h"
#include "../Object/Gimmick/GimmickShop.h"
#include "../Object/Gimmick/GimmickDropRock.h"
#include "GimmickGenerator.h"

GimmickGenerator::GimmickGenerator()
{
	createGimmickMap_.emplace(GimmickTypes::TYPE::DOOR, [this]()
		{
			return CreateGimmickDoor();
		});
	createGimmickMap_.emplace(GimmickTypes::TYPE::TARGET, [this]()
		{
			return CreateGimmickTarget();
		});
	createGimmickMap_.emplace(GimmickTypes::TYPE::TREASURE_CHEST, [this]()
		{
			return CreateGimmickTreasureChest();
		});
	createGimmickMap_.emplace(GimmickTypes::TYPE::BAMBOO, [this]()
		{
			return CreateGimmickBamboo();
		});
	createGimmickMap_.emplace(GimmickTypes::TYPE::GROWING_BAMBOO, [this]()
		{
			return CreateGimmickGrowingBamboo();
		});
	createGimmickMap_.emplace(GimmickTypes::TYPE::SHOP, [this]()
		{
			return CreateGimmickShop();
		});
	createGimmickMap_.emplace(GimmickTypes::TYPE::DROP_ROCK, [this]()
		{
			return CreateGimmickDropRock();
		});
	createGimmickMap_.emplace(GimmickTypes::TYPE::GROUND_ROCK, [this]()
		{
			return CreateGimmickDropRock();
		});
}

GimmickGenerator::~GimmickGenerator()
{
}

void GimmickGenerator::InitParameter()
{
	// 情報の取得
	const auto jsonParameterMap = UtilityLoad::GetJsonMapArrayData("GimmickParameter");

	// ドア生成
	const auto jsonDoorParameter = jsonParameterMap.at("door").front();
	auto parameterDoor = std::make_unique<ParameterGimmick>();
	parameterDoor->LoadParameter(jsonDoorParameter);
	templateParameterMap_.emplace(GimmickTypes::TYPE::DOOR, std::move(parameterDoor));

	// ターゲット生成
	const auto jsonTargetParameter = jsonParameterMap.at("target").front();
	auto parameterTarget = std::make_unique<ParameterGimmickTarget>();
	parameterTarget->LoadParameter(jsonTargetParameter);
	templateParameterMap_.emplace(GimmickTypes::TYPE::TARGET, std::move(parameterTarget));

	// 宝箱生成
	const auto jsonTreasureChestParameter = jsonParameterMap.at("treasureChest").front();
	auto parameterTreasureChest = std::make_unique<ParameterGimmickTreasureChest>();
	parameterTreasureChest->LoadParameter(jsonTreasureChestParameter);
	templateParameterMap_.emplace(GimmickTypes::TYPE::TREASURE_CHEST, std::move(parameterTreasureChest));

	// 竹生成
	const auto jsonBambooParameter = jsonParameterMap.at("bamboo").front();
	auto parameterBamboo = std::make_unique<ParameterGimmickBamboo>();
	parameterBamboo->LoadParameter(jsonBambooParameter);
	templateParameterMap_.emplace(GimmickTypes::TYPE::BAMBOO, std::move(parameterBamboo));

	// 成長する竹生成
	const auto jsonGrowingBambooParameter = jsonParameterMap.at("growingBamboo").front();
	auto parameterGrowingBamboo = std::make_unique<ParameterGimmickGrowingBamboo>();
	parameterGrowingBamboo->LoadParameter(jsonGrowingBambooParameter);
	templateParameterMap_.emplace(GimmickTypes::TYPE::GROWING_BAMBOO, std::move(parameterGrowingBamboo));

	// 店生成
	const auto jsonShopParameter = jsonParameterMap.at("shop").front();
	auto parameterShop = std::make_unique<ParameterGimmick>();
	parameterShop->LoadParameter(jsonShopParameter);
	templateParameterMap_.emplace(GimmickTypes::TYPE::SHOP, std::move(parameterShop));

	//岩落とし
	const auto jsonDropRockParameter = jsonParameterMap.at("dropRock").front();
	auto parameterDropRock = std::make_unique<ParameterGimmick>();
	parameterDropRock->LoadParameter(jsonDropRockParameter);
	templateParameterMap_.emplace(GimmickTypes::TYPE::DROP_ROCK, std::move(parameterDropRock));
}

std::unique_ptr<GimmickBase> GimmickGenerator::Create(const GimmickTypes::TYPE type)
{
	// 必要とするものがあるか探索
	auto it = createGimmickMap_.find(type);

	// ある場合
	if (it != createGimmickMap_.end())
	{
		// 生成したものを返す
		return it->second();
	}

	// 見つからない場合空で返す
	return nullptr;
}

std::unique_ptr<GimmickTarget> GimmickGenerator::CreateTarget(const Vector2F pos, const Vector2F& moveDir)
{
	auto target = CreateGimmickTarget();
	auto& parameter = target->GetParameter();
	parameter.pos_ = pos;
	parameter.moveDir_ = moveDir;
	parameter.isMove_ = moveDir.x != 0.0f || moveDir.y != 0.0f;
	return target;
}

std::unique_ptr<GimmickDoor> GimmickGenerator::CreateGimmickDoor()
{
	return std::make_unique<GimmickDoor>(std::move(std::make_unique<ParameterGimmick>(*templateParameterMap_.at(GimmickTypes::TYPE::DOOR))));
}

std::unique_ptr<GimmickTarget> GimmickGenerator::CreateGimmickTarget()
{
	// 専用のパラメータにキャスト
	auto parameterBase = templateParameterMap_.at(GimmickTypes::TYPE::TARGET).get();
	auto parameterTarget = dynamic_cast<ParameterGimmickTarget*>(parameterBase);

	// 空の場合
	if (parameterTarget == nullptr)
	{
		// 空で返す
		return nullptr;
	}

	// 生成したものを返す
	auto parameter = std::make_unique<ParameterGimmickTarget>(*parameterTarget);
	return std::make_unique<GimmickTarget>(std::move(parameter));
}

std::unique_ptr<GimmickBamboo> GimmickGenerator::CreateGimmickBamboo()
{
	// 専用のパラメータにキャスト
	auto parameterBase = templateParameterMap_.at(GimmickTypes::TYPE::BAMBOO).get();
	auto parameterBamboo = dynamic_cast<ParameterGimmickBamboo*>(parameterBase);

	// 空の場合
	if (parameterBamboo == nullptr)
	{
		// 空で返す
		return nullptr;
	}

	// 生成したものを返す
	auto parameter = std::make_unique<ParameterGimmickBamboo>(*parameterBamboo);
	return std::make_unique<GimmickBamboo>(std::move(parameter));
}

std::unique_ptr<GimmickGrowingBamboo> GimmickGenerator::CreateGimmickGrowingBamboo()
{
	// 専用のパラメータにキャスト
	auto parameterBase = templateParameterMap_.at(GimmickTypes::TYPE::GROWING_BAMBOO).get();
	auto parameterGrowingBamboo = dynamic_cast<ParameterGimmickGrowingBamboo*>(parameterBase);

	// 空の場合
	if (parameterGrowingBamboo == nullptr)
	{
		// 空で返す
		return nullptr;
	}

	// 生成したものを返す
	auto parameter = std::make_unique<ParameterGimmickGrowingBamboo>(*parameterGrowingBamboo);
	return std::make_unique<GimmickGrowingBamboo>(std::move(parameter));
}

std::unique_ptr<GimmickTreasureChest> GimmickGenerator::CreateGimmickTreasureChest()
{
	// 専用のパラメータにキャスト
	auto parameterBase = templateParameterMap_.at(GimmickTypes::TYPE::TREASURE_CHEST).get();
	auto parameterTreasureChest = dynamic_cast<ParameterGimmickTreasureChest*>(parameterBase);

	// 空の場合
	if (parameterTreasureChest == nullptr)
	{
		// 空で返す
		return nullptr;
	}

	// 生成したものを返す
	auto parameter = std::make_unique<ParameterGimmickTreasureChest>(*parameterTreasureChest);
	return std::make_unique<GimmickTreasureChest>(std::move(parameter));
}

std::unique_ptr<GimmickShop> GimmickGenerator::CreateGimmickShop()
{
	// 専用のパラメータにキャスト
	auto parameterShop = templateParameterMap_.at(GimmickTypes::TYPE::SHOP).get();

	// 空の場合
	if (parameterShop == nullptr)
	{
		// 空で返す
		return nullptr;
	}

	// 生成したものを返す
	auto parameter = std::make_unique<ParameterGimmick>(*parameterShop);
	return std::make_unique<GimmickShop>(std::move(parameter));
}

std::unique_ptr<GimmickDropRock> GimmickGenerator::CreateGimmickDropRock()
{
	// 専用のパラメータにキャスト
	auto parameterBase = templateParameterMap_.at(GimmickTypes::TYPE::DROP_ROCK).get();
	auto parameterDropRock = dynamic_cast<ParameterGimmick*>(parameterBase);

	// 空の場合
	if (parameterDropRock == nullptr)
	{
		// 空で返す
		return nullptr;
	}

	// 生成したものを返す
	auto parameter = std::make_unique<ParameterGimmick>(*parameterDropRock);
	return std::make_unique<GimmickDropRock>(std::move(parameter));
}

std::unique_ptr<GimmickDropRock> GimmickGenerator::CreateGimmickGroundRock()
{
	// 専用のパラメータにキャスト
	auto parameterBase = templateParameterMap_.at(GimmickTypes::TYPE::GROUND_ROCK).get();
	auto parameterGroundRock = dynamic_cast<ParameterGimmick*>(parameterBase);

	// 空の場合
	if (parameterGroundRock == nullptr)
	{
		// 空で返す
		return nullptr;
	}

	// 生成したものを返す
	auto parameter = std::make_unique<ParameterGimmick>(*parameterGroundRock);
	return std::make_unique<GimmickDropRock>(std::move(parameter));
}
