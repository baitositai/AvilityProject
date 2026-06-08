#pragma once
#include "SceneBase.h"

class SceneGameOver : public SceneBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	SceneGameOver();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SceneGameOver() override;

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