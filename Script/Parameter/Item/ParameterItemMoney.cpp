#include <Windows.h>
#include "ParameterItemMoney.h"

ParameterItemMoney::ParameterItemMoney():
	amount_(-1)
{
}

ParameterItemMoney::~ParameterItemMoney()
{
}

void ParameterItemMoney::LoadParameter(const Json& parameter, const std::string& name)
{
	// 基底クラスの処理
	ParameterItem::LoadParameter(parameter);

	// 個別のパラメータ読み込み
	amount_ = parameter.value("amount", -1);

	// お宝共通のパラメータ読み込み
	const auto& jsonCommonParameter = parameter.at("moneyCommon").front();
	ParameterActor::LoadParameter(jsonCommonParameter);

	// 個別のパラメータ読み込み
	try
	{
		// 指定されたキーが存在するかチェック
		if (parameter.contains("money"))
		{
			const auto& jsonMoney = parameter.at("money").front();

			// 指定された名前のキーが存在するかチェック
			if (jsonMoney.contains(name))
			{
				const auto& jsonMoneyParameter = jsonMoney.at(name);
				amount_ = jsonMoneyParameter.value("amount", -1);
				spriteIndex_ = jsonMoneyParameter.value("index", -1);
				resourceKey_ = jsonMoneyParameter.value("resourceKey", "");
				if (jsonMoneyParameter.contains("hitBoxSize"))
				{
					hitSize_.x = jsonMoneyParameter["hitBoxSize"].value("x", 0);
					hitSize_.y = jsonMoneyParameter["hitBoxSize"].value("y", 0);
				}
				if (jsonMoneyParameter.contains("divisionNum"))
				{
					divisionNum_.x = jsonMoneyParameter["divisionNum"].value("x", 1);
					divisionNum_.y = jsonMoneyParameter["divisionNum"].value("y", 1);
				}
				LoadParameterAnimation(jsonMoneyParameter);
			}
		}
	}
	catch (const std::exception& e)
	{
		OutputDebugStringA(e.what());
	}
}
