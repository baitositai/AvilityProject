#pragma once
#include "ItemBase.h"
#include "../../Parameter/Item/ParameterItemTreasure.h"

class ItemTreasure : public ItemBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ</param>
	explicit ItemTreasure(std::unique_ptr<ParameterItemTreasure> parameter);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ItemTreasure() override;

	/// <summary>
	/// パラメーターを返す(変更可)
	/// </summary>
	/// <returns>パラメータ</returns>
	ParameterItemTreasure& GetParameter() { return *parameterItemTreasure_; }

	/// <summary>
	/// パラメータを返す
	/// </summary>
	/// <returns>パラメータ</returns>
	const ParameterItemTreasure& GetParameter() const { return *parameterItemTreasure_; }

private:

	// パラメータ情報
	ParameterItemTreasure* parameterItemTreasure_;
};