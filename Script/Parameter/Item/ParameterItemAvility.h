#pragma once
#include "ParameterItem.h"
#include "../../Component/Avility/AvilityTypes.h"

class ParameterItemAvility : public ParameterItem
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ParameterItemAvility();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ParameterItemAvility() override;

	/// <summary>
	/// 読み込み
	/// </summary>
	/// <param name="parameter">パラメータ</param>
	/// <param name="name">名前</param>
	void LoadParameter(const Json& parameter, std::string& name);
	
	/// <summary>
	/// アビリティ種類の設定
	/// </summary>
	/// <param name="type">種類</param>
	void SetAvilityType(const AvilityTypes::TYPE type) { type_ = type; }

	// 種類
	AvilityTypes::TYPE type_;
};