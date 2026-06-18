#pragma once
#include <memory>
#include "SceneBase.h"

class ScenePause;

class SceneTrain : public SceneBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	SceneTrain();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SceneTrain() override;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// シーン遷移の準備
	/// </summary>
	void SceneChangeReady() override;

private:

	// ポーズ画面
	std::shared_ptr<ScenePause> ScenePause_;

	// 更新関数
	void NormalUpdate() override;

	// 描画関数
	void NormalDraw() override;

	//デバッグ処理
	void DebugUpdate();
	void DebugDraw();
};