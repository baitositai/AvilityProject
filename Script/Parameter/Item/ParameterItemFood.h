#pragma once
#include "ParameterItem.h"

class ParameterItemFood : public ParameterItem
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ParameterItemFood();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ParameterItemFood() override;

	/// <summary>
	/// 読み込み
	/// </summary>
	/// <param name="parameter">パラメータ</param>
	/// <param name="name">名前</param>
	void LoadParameter(const Json& parameter, std::string& name);

	// 回復量
	int heal_;
};