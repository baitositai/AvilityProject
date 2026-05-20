#pragma once
#include "ItemBase.h"
#include "../../Parameter/Item/ParameterItemAvility.h"
#include "../../Component/Avility/AvilityTypes.h"

class ItemAvility : public ItemBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ情報</param>
	explicit ItemAvility(std::unique_ptr<ParameterItemAvility> parameter);

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
	ParameterItemAvility* parameterItemAvility_;
};

