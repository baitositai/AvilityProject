#include <Windows.h>
#include "ParameterItemTreasure.h"

ParameterItemTreasure::ParameterItemTreasure() :
	amount_(-1)
{
}

ParameterItemTreasure::~ParameterItemTreasure()
{
}

void ParameterItemTreasure::LoadParameter(const Json& parameter, std::string& name)
{
	// お宝共通のパラメータ読み込み
	const auto& jsonCommonParameter = parameter.at("treasureCommon").front();
	ParameterActor::LoadParameter(jsonCommonParameter);

	// 個別のパラメータ読み込み
	try
	{
		// 指定されたキーが存在するかチェック
		if (parameter.contains("treasure"))
		{
			const auto& jsonTreasures = parameter.at("treasure").front();

			// 指定された名前のキーが存在するかチェック
			if (jsonTreasures.contains(name))
			{
				const auto& jsonTreasureParameter = jsonTreasures.at(name);
				amount_ = jsonTreasureParameter.value("amount", -1);
				spriteIndex_ = jsonTreasureParameter.value("index", -1);
				resourceKey_ = jsonTreasureParameter.value("resourceKey", "");
				if (jsonTreasureParameter.contains("hitBoxSize"))
				{
					hitSize_.x = jsonTreasureParameter["hitBoxSize"].value("x", 0);
					hitSize_.y = jsonTreasureParameter["hitBoxSize"].value("y", 0);
				}
			}
		}
	}
	catch (const std::exception& e)
	{
		OutputDebugStringA(e.what());
	}
}