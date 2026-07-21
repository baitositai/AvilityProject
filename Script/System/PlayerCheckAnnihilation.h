#pragma once
#include <functional>
#include <unordered_map>

class SceneManager;
class PlayerManager;
class UiPlayerAnnhilation;

class PlayerCheckAnnihilation
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerCheckAnnihilation();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerCheckAnnihilation();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// タイマー時間を返す
	/// </summary>
	/// <returns>タイマー時間</returns>
	const int GetTimer() const { return static_cast<int>(timer_); }

private:

	// 終了時間
	static constexpr float END_TIME = 5.0f;

	// プレイヤー管理クラス
	PlayerManager& playerManager_;

	// シーン管理クラス
	SceneManager& sceneManager_;	
	
	// タイマー
	float timer_;

	// 全滅判定のバックアップ
	bool isPreAnnihilation_;

	// UI
	UiPlayerAnnhilation* uiPlayerAnnhilation_;

	// 判定別遷移処理管理
	std::unordered_map<bool, std::function<void()>> changeFunctionMap_;

	// 全滅時の遷移処理
	void ChnageAnnihilation();
	void ChangeAlive();
};