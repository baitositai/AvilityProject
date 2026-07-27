#pragma once
#include <memory>
#include "SceneBase.h"
#include "../Manager/Common/SoundType.h"

class GameStart;

class SceneGame : public SceneBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	SceneGame();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SceneGame() override;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

private:

	// ゲーム開始
	std::unique_ptr<GameStart> gameStart_;

	// 更新処理
	std::function<void()> gameUpdate_;

	// 再生しているBGM種類
	SoundType::BGM soundType_;

	// 更新関数
	void NormalUpdate() override;

	// 描画関数
	void NormalDraw() override;

	// 更新処理
	void UpdateGameStart();
	void UpdateGameMain();

	//デバッグ処理
	void DebugUpdate() override;
	void DebugDraw() override;
};