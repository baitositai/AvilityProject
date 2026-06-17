#pragma once
#include "ParameterGimmick.h"

class ParameterGimmickTreasureChest : public ParameterGimmick
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ParameterGimmickTreasureChest();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ParameterGimmickTreasureChest() override;

	/// <summary>
	/// 読み込み
	/// </summary>
	/// <param name="parameter">パラメータ</param>
	void LoadParameter(const Json& parameter) override;

};