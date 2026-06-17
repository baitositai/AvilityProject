#include "../Utility/UtilityLoad.h"
#include "../Object/Gimmick/GimmickDoor.h"
#include "../Object/Gimmick/GimmickTarget.h"
#include "GimmickGenerator.h"

GimmickGenerator::GimmickGenerator()
{
	// 生成処理の登録
	createGimmickMap_.emplace(GimmickTypes::TYPE::DOOR, [this]()
		{
			return CreateGimmickDoor();
		});
	createGimmickMap_.emplace(GimmickTypes::TYPE::TARGET, [this]()
		{
			return CreateGimmickTarget();
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