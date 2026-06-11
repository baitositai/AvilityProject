#pragma once
#include <nlohmann/json.hpp>

// JSON名前空間
using Json = nlohmann::json;

class ParameterBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ParameterBase();

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~ParameterBase();

	/// <summary>
	/// 読み込み
	/// </summary>
	/// <param name="parameter">パラメータ</param>
	virtual void LoadParameter(const Json& parameter);
};

