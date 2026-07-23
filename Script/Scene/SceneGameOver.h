#pragma once
#include "SceneBase.h"
#include "../Common/Image.h"

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

	// 背景
	Image backGround_;

	// キー入力
	Image pleaseButton_;

	// 更新関数
	void NormalUpdate() override;

	// 描画関数
	void NormalDraw() override;
};