#pragma once
#include "ParameterItem.h"

class ParameterItemMoney : public ParameterItem
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ParameterItemMoney();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ParameterItemMoney() override;

	/// <summary>
	/// 読み込み
	/// </summary>
	/// <param name="parameter">パラメータ</param>
	void LoadParameter(const Json& parameter, const std::string& name);

	// お金量
	int amount_;
};