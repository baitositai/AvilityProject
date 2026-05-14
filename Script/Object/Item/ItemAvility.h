#pragma once
#include "ItemBase.h"
#include "../../Component/Avility/AvilityTypes.h"

class ItemAvility : public ItemBase
{
public:

	struct Parameter : public ItemBase::Parameter
	{
		AvilityTypes::TYPE type = AvilityTypes::TYPE::MAX;
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

	/// <summary>
	/// 生成するコンポーネントの名前を返す
	/// </summary>
	/// <returns>コンポーネント名前</returns>
	const std::string GetCreateAvilityName() const;

private:

	// パラメータ
	Parameter parameter_;
};

