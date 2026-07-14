#include <Windows.h>
#include "ParameterItemFood.h"
#include "../../Utility/UtilityCommon.h"

ParameterItemFood::ParameterItemFood() :
	heal_(-1)
{
	itemType_ = ItemTypes::TYPE::FOOD;
}

ParameterItemFood::~ParameterItemFood()
{
}

void ParameterItemFood::LoadParameter(const Json& parameter, std::string& name)
{
	// 食べ物共通のパラメータ読み込み
	const auto& jsonCommonParameter = parameter.at("foodCommon").front();
	shopMessage_ = UtilityCommon::ConvertUtf8ToSjis((jsonCommonParameter.value("shopMessage", "").c_str()));
	ParameterActor::LoadParameter(jsonCommonParameter);

	// 個別のパラメータ読み込み
	try
	{
		// 指定されたキーが存在するかチェック
		if (parameter.contains("foods"))
		{
			const auto& jsonFoods = parameter.at("foods").front();

			// 指定された名前のキーが存在するかチェック
			if (jsonFoods.contains(name))
			{
				const auto& jsonFoodParameter = jsonFoods.at(name);
				heal_ = jsonFoodParameter.value("healHp", -1);
				spriteIndex_ = jsonFoodParameter.value("index", -1);
				amount_ = jsonFoodParameter.value("amount", -1);
			}
		}
	}
	catch (const std::exception& e)
	{
		OutputDebugStringA(e.what());
	}
}