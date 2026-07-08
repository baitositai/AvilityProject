#pragma once
#include "ItemBase.h"
#include "../../Parameter/Item/ParameterItemPotion.h"

class ItemPotion : public ItemBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ情報</param>
	ItemPotion(std::unique_ptr<ParameterItemPotion> parameter);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ItemPotion() override;

	/// <summary>
	/// 初期化
	/// </summary>
	void Init() override;

	/// <summary>
	/// パラメーターを返す(変更可)
	/// </summary>
	/// <returns>パラメータ</returns>
	ParameterItemPotion& GetParameter() { return *parameterItemPotion_; }

	/// <summary>
	/// パラメータを返す
	/// </summary>
	/// <returns>パラメータ</returns>
	const ParameterItemPotion& GetParameter() const { return *parameterItemPotion_; }

private:

	// パラメータ情報
	ParameterItemPotion* parameterItemPotion_;

};