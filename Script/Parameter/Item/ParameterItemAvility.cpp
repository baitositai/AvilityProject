#include <Windows.h>
#include "../../Utility/UtilityCommon.h"
#include "ParameterItemAvility.h"

ParameterItemAvility::ParameterItemAvility() :
	type_(AvilityTypes::TYPE::MAX)
{
	itemType_ = ItemTypes::TYPE::AVILITY;
}

ParameterItemAvility::~ParameterItemAvility()
{
}

void ParameterItemAvility::LoadParameter(const Json& parameter, std::string& name)
{
	// アビリティ共通のパラメータ読み込み
	const auto& jsonCommonParameter = parameter.at("avilityCommon").front();
	ParameterActor::LoadParameter(jsonCommonParameter);

	// 個別のパラメータ読み込み
	try
	{
		// 指定されたキーが存在するかチェック
		if (parameter.contains("abilities"))
		{
			const auto& jsonAbilities = parameter.at("abilities").front();

			// 指定された名前のキーが存在するかチェック
			if (jsonAbilities.contains(name))
			{
				const auto& jsonAvilityParameter = jsonAbilities.at(name);
				spriteIndex_ = jsonAvilityParameter.value("index", -1);
				amount_ = jsonAvilityParameter.value("amount", -1);
				shopMessage_ = UtilityCommon::ConvertUtf8ToSjis((jsonAvilityParameter.value("shopMessage", "").c_str()));
			}
		}
	}
	catch (const std::exception& e)
	{
		OutputDebugStringA(e.what());
	}
}