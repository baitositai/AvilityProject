#include "../Utility/UtilityLoad.h"
#include "../Object/Gimmick/GimmickDoor.h"
#include "../Object/Gimmick/GimmickTarget.h"
#include "../Object/Gimmick/GimmickTreasureChest.h"
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
