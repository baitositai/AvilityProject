#include "../../Utility/UtilityCommon.h"
#include "ParameterItemPotion.h"

ParameterItemPotion::ParameterItemPotion() :
	attackUp_(-1),
	hpMaxUp_(-1),
	speedUp_(0.0f),
	tag_(CollisionTags::TAG::MAX)
{
}

ParameterItemPotion::~ParameterItemPotion()
{
}

void ParameterItemPotion::LoadParameter(const Json& parameter, std::string& name)
{
	// 共通のパラメータ読み込み
	const auto& jsonCommonParameter = parameter.at("potionCommon").front();
	ParameterActor::LoadParameter(jsonCommonParameter);

	// 個別のパラメータ読み込み
	try
	{
		// 指定されたキーが存在するかチェック
		if (parameter.contains("potions"))
		{
			const auto& jsonPotions = parameter.at("potions").front();

			// 指定された名前のキーが存在するかチェック
			if (jsonPotions.contains(name))
			{
				const auto& jsonPotionParameter = jsonPotions.at(name);
				attackUp_ = jsonPotionParameter.value("attackUp", -1);
				hpMaxUp_ = jsonPotionParameter.value("hpMaxUp", -1);
				speedUp_ = jsonPotionParameter.value("speedUp", 0.0f);
				spriteIndex_ = jsonPotionParameter.value("index", -1);
				amount_ = jsonPotionParameter.value("amount", -1);
				shopMessage_ = UtilityCommon::ConvertUtf8ToSjis((jsonPotionParameter.value("shopMessage", "").c_str()));
				if (NAME_TAG_MAP.contains(name))
				{
					tag_ = NAME_TAG_MAP.at(name);
				}
			}
		}
	}
	catch (const std::exception& e)
	{
		OutputDebugStringA(e.what());
	}
}