#pragma once
#include "GimmickBase.h"
class GimmickShop : public GimmickBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ情報</param>
	GimmickShop(std::unique_ptr<ParameterGimmick> parameter);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GimmickShop() override;

	/// <summary>
	/// 初期化
	/// </summary>
	void Init() override;

private:

	// パラメータ情報
	ParameterGimmick* parameterShop_;

};