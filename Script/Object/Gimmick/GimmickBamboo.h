#pragma once
#include "GimmickBase.h"
#include "../../Parameter/Gimmick/ParameterGimmickBamboo.h"

class GimmickBamboo : public GimmickBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ情報</param>
	GimmickBamboo(std::unique_ptr<ParameterGimmickBamboo> parameter);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GimmickBamboo() override;

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
	ParameterGimmickBamboo& GetParameter() { return *parameterBamboo_; }

	/// <summary>
	/// パラメータを返す
	/// </summary>
	/// <returns>パラメータ</returns>
	const ParameterGimmickBamboo& GetParameter() const { return *parameterBamboo_; }

private:

	ParameterGimmickBamboo* parameterBamboo_;
};

