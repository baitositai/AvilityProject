#pragma once
#include "ItemBase.h"
#include "../../Component/Avility/AvilityList.h"

class ItemAvility : public ItemBase
{
public:

	struct Parameter : public ItemBase::Parameter
	{
		AVILITY_TYPE type = AVILITY_TYPE::MAX;
	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ情報</param>
	/// <param name="componentNameList">コンポーネント名リスト</param>
	ItemAvility(Parameter& parameter, const std::vector<std::string>& componentNameList = {});

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ItemAvility() override;

private:

	// パラメータ
	Parameter parameter_;
};

