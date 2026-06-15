#pragma once
#include "GimmickBase.h"
#include "../../Parameter/Gimmick/ParameterGimmickTarget.h"

class GimmickTarget : public GimmickBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ情報</param>
	GimmickTarget(std::unique_ptr<ParameterGimmickTarget> parameter);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GimmickTarget() override;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

private:

	// パラメータ情報
	ParameterGimmickTarget* parameterTarget_;

};