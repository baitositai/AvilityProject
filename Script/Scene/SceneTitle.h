#pragma once
#include <unordered_map>
#include "../../Common/Image.h"
#include "SceneBase.h"

class Train;

class SceneTitle : public SceneBase
{

public:

	// コンストラクタ
	SceneTitle();

	// デストラクタ
	~SceneTitle() override;

	// 初期化処理
	void Init() override;

private:

	// タイトルロゴ
	Image titleLogo_;

	// トレイン
	std::unique_ptr<Train> train_;

	// 荷物
	std::unique_ptr<Train> carriage_;

	// 更新関数
	void NormalUpdate() override;

	// 描画関数
	void NormalDraw() override;
};