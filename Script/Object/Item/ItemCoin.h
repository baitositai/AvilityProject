#pragma once
#include "ItemBase.h"
#include "../../Parameter/Item/ParameterItemMoney.h"

class ItemCoin : public ItemBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	explicit ItemCoin(std::unique_ptr<ParameterItemMoney> parameter);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ItemCoin() override;

	/// <summary>
	/// パラメーターを返す(変更可)
	/// </summary>
	/// <returns>パラメータ</returns>
	ParameterItemMoney& GetParameter() { return *parameterItemMoney_; }

	/// <summary>
	/// パラメータを返す
	/// </summary>
	/// <returns>パラメータ</returns>
	const ParameterItemMoney& GetParameter() const { return *parameterItemMoney_; }

private:

	// パラメータ情報
	ParameterItemMoney* parameterItemMoney_;
};