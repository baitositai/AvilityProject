#pragma once
#include "ParameterItem.h"
class ParameterItemTreasure : public ParameterItem
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ParameterItemTreasure();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ParameterItemTreasure() override;

	/// <summary>
	/// 読み込み
	/// </summary>
	/// <param name="parameter">パラメータ</param>
	/// <param name="name">名前</param>
	void LoadParameter(const Json& parameter, std::string& name);

	// 金額
	int amount_;
};