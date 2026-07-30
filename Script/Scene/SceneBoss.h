#pragma once
#include <memory>
#include "SceneBase.h"
#include "../Manager/Game/EnemyTypes.h"

class GameStart;

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

	// シーン遷移用遅延
	static constexpr float SCENE_CHANGE_DELAY = 5.0f;

	// ゲーム開始
	std::unique_ptr<GameStart> gameStart_;

	// 更新処理
	std::function<void()> gameUpdate_;

	// シーン遷移時間
	float sceneChangeTimer_;
	bool isSceneChanges_;
	// ボス種類
	EnemyTypes::TYPE bossType_;

	// 更新処理
	void UpdateGameStart();
	void UpdateGameMain();

	// 更新関数
	void NormalUpdate() override;

	// 描画関数
	void NormalDraw() override;

	//デバッグ処理
	void DebugUpdate() override;
	void DebugDraw() override;
};