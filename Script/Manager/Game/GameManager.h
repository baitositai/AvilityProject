#pragma once
#include <list>
#include <functional>
#include <unordered_map>	
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
	/// 状態遷移
	/// </summary>
	/// <param name="state">状態</param>
	void ChangeState(const STATE state);

	/// <summary>
	/// デバッグ描画
	/// </summary>
	void DebugDraw();

private:

	// 現在の状態
	STATE state_;	
	
	// ステージ
	std::unique_ptr<Stage> stage_;

	// 状態遷移の関数マップ
	std::unordered_map<STATE, std::function<void()>> changeStateMap_;

	// ゲーム状態別処理
	std::unique_ptr<GameStateBase> game_;

	// 各種状態遷移関数
	void ChangeStateRoad();
	void ChangeStateBoss();
	void ChangeStateEvent();

	// コンストラクタ
	GameManager();

	// デストラクタ
	~GameManager();
};

