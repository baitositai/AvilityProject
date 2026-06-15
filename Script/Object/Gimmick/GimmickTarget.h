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

	/// <summary>
	/// パラメーターを返す(変更可)
	/// </summary>
	/// <returns>パラメータ</returns>
	ParameterGimmickTarget& GetParameter() { return *parameterTarget_; }

	/// <summary>
	/// パラメータを返す
	/// </summary>
	/// <returns>パラメータ</returns>
	const ParameterGimmickTarget& GetParameter() const { return *parameterTarget_; }

private:

	// パラメータ情報
	ParameterGimmickTarget* parameterTarget_;

	Vector2F prePos_;

	// カメラ範囲内か判定
	bool CheckCameraRange();

	// 前回位置から動いたか判定
	bool IsCheckPrePos();
};