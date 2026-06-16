#pragma once
#include "ItemBase.h"
#include "../../Parameter/Item/ParameterItemFood.h"

class ItemFood : public ItemBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ情報</param>
	explicit ItemFood(std::unique_ptr<ParameterItemFood> parameter);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ItemFood() override;

	/// <summary>
	/// パラメーターを返す(変更可)
	/// </summary>
	/// <returns>パラメータ</returns>
	ParameterItemFood& GetParameter() { return *parameterItemFood_; }

	/// <summary>
	/// パラメータを返す
	/// </summary>
	/// <returns>パラメータ</returns>
	const ParameterItemFood& GetParameter() const { return *parameterItemFood_; }

private:

	// パラメータ情報
	ParameterItemFood* parameterItemFood_;
};