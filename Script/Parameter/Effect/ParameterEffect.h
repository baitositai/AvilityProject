#pragma once
#include "../ParameterActor.h"
#include "../../Manager/Game/CollisionTags.h"

class ParameterEffect : public ParameterActor
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ParameterEffect();
	
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~ParameterEffect() override;

	/// <summary>
	/// パラメータの読み込み
	/// </summary>
	/// <param name="parameter">パラメータ情報</param>
	virtual void LoadParameter(const Json& parameter) override;

	// コライダータグ
	CollisionTags::TAG tag_;

	// ループ判定
	bool isLoop_;
};