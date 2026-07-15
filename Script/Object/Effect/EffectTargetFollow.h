#pragma once
#include "EffectBase.h"

class ActorBase;

class EffectTargetFollow : public EffectBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ情報</param>
	EffectTargetFollow(std::unique_ptr<ParameterEffect> parameter);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EffectTargetFollow() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// ターゲットの設定
	/// </summary>
	/// <param name="target">ターゲット</param>
	void SetTarget(const ActorBase* target);

private:

	// ターゲット
	const ActorBase* target_;

	// パラメータ情報
	ParameterEffect* parameterEffect_;
};