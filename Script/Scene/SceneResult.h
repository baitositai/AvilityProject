#pragma once
#include "SceneBase.h"
#include "../Common/Image.h"

class SceneResult : public SceneBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	SceneResult();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SceneResult() override;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

private:

	// 背景
	Image backGround_;

	// 更新関数
	void NormalUpdate() override;

	// 描画関数
	void NormalDraw() override;
};