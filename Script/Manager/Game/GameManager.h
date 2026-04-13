#pragma once
#include <list>
#include "../../Template/Singleton.h"

class GameStateBase;
class Stage;

class GameManager : public Singleton<GameManager>
{
	//シングルトンにだけ共有する
	friend class Singleton<GameManager>;

public:

	// 状態
	enum class STATE
	{
		ROAD,		// ロード
		BOSS,		// ボス
		EVENT,		// イベント
		MAX
	};

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// デバッグ描画
	/// </summary>
	void DebugDraw();

private:

	// ゲーム状態リスト
	std::list<std::unique_ptr<GameStateBase>> gameStateList_;

	// ステージ
	std::unique_ptr<Stage> stage_;

	// コンストラクタ
	GameManager();

	// デストラクタ
	~GameManager();

};

