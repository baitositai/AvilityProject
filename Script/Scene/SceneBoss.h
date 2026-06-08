#pragma once
#include <memory>
#include "SceneBase.h"

class ScenePause;

class SceneBoss : public SceneBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	SceneBoss();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SceneBoss() override;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

private:

	//ポーズ画面
	std::shared_ptr<ScenePause> ScenePause_;

	// 更新関数
	void NormalUpdate() override;

	// 描画関数
	void NormalDraw() override;

	//デバッグ処理
	void DebugUpdate() override;
	void DebugDraw() override;
};