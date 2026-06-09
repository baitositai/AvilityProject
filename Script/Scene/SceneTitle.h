#pragma once
#include <unordered_map>
#include "../../Common/Image.h"
#include "SceneBase.h"

class Train;
class BackGround;

class SceneTitle : public SceneBase
{

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	SceneTitle();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SceneTitle() override;

	/// <summary>
	/// 初期化
	/// </summary>
	void Init() override;

private:

	// タイトルロゴ
	Image titleLogo_;

	// トレイン
	std::unique_ptr<Train> train_;

	// 背景
	std::unique_ptr<BackGround> backGround_;

	// 更新関数
	void NormalUpdate() override;

	// 描画関数
	void NormalDraw() override;
};