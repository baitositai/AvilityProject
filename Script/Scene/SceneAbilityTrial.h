#pragma once
#include "SceneBase.h"

class SceneAbilityTrial : public SceneBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	SceneAbilityTrial();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SceneAbilityTrial() override;
	
	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

private:

	// 更新関数
	void NormalUpdate() override;

	// 描画関数
	void NormalDraw() override;
};

