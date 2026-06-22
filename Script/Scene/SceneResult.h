#pragma once
#include "SceneBase.h"
#include "../Common/Image.h"
#include "../Common/CharacterString.h"

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

	// スコアテキスト
	CharacterString scoreText_;

	// 背景
	Image backGround_;

	// 更新関数
	void NormalUpdate() override;

	// 描画関数
	void NormalDraw() override;
};