#pragma once
#include "GimmickBase.h"
#include "../../Parameter/Gimmick/ParameterGimmickGrowingBamboo.h"

class GimmickGrowingBamboo : public GimmickBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ情報</param>
	GimmickGrowingBamboo(std::unique_ptr<ParameterGimmickGrowingBamboo> parameter);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GimmickGrowingBamboo() override;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// パラメーターを返す(変更可)
	/// </summary>
	/// <returns>パラメータ</returns>
	ParameterGimmickGrowingBamboo& GetParameter() { return *parameterBamboo_; }

	/// <summary>
	/// パラメータを返す
	/// </summary>
	/// <returns>パラメータ</returns>
	const ParameterGimmickGrowingBamboo& GetParameter() const { return *parameterBamboo_; }

private:

	// パラメータ情報
	ParameterGimmickGrowingBamboo* parameterBamboo_;
};

