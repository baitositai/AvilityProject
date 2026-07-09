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

	/// <summary>
	/// リソース指定用番号を返す
	/// </summary>
	/// <returns></returns>
	const int GetAvilityItemResourceIndex() const;

	/// <summary>
	/// パラメーターを返す(変更可)
	/// </summary>
	/// <returns>パラメータ</returns>
	ParameterItemAvility& GetParameter() { return *parameterItemAvility_; }

	/// <summary>
	/// パラメータを返す
	/// </summary>
	/// <returns>パラメータ</returns>
	const ParameterItemAvility& GetParameter() const { return *parameterItemAvility_; }

private:

	// パラメータ
	ParameterItemAvility* parameterItemAvility_;
};

