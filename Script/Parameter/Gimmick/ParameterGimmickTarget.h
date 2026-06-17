#pragma once
#include "ParameterGimmick.h"
class ParameterGimmickTarget : public ParameterGimmick
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ParameterGimmickTarget();
	
	/// <summary>
	/// デストラクタ
	/// </summary>
	~ParameterGimmickTarget() override;

	/// <summary>
	/// 読み込み
	/// </summary>
	/// <param name="parameter">パラメータ</param>
	void LoadParameter(const Json& parameter) override;

	// 移動判定
	bool isMove_;

	// 移動制限
	Vector2 moveLimit_;

	// 移動方向
	Vector2F moveDir_;
};