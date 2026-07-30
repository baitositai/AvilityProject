#pragma once
#include <memory>
#include <chrono>
#include <list>
#include "../../Template/Singleton.h"
#include "../../Common/Fader.h"
#include "../../Common/Vector2.h"
#include "../../Manager/Common/Input.h"

//カメラのマクロ
#define mainCamera SceneManager::GetInstance().GetCamera()

class SceneBase;
class SceneShop;
class Fader;
class Camera;

class SceneManager : public Singleton<SceneManager>
{
	//シングルトンにだけ共有する
	friend class Singleton<SceneManager>; 

public:

	// フォグの開始位置と終了位置
	static constexpr float FOG_START = 2000.0f;
	static constexpr float FOG_END = 3000.0f;

	// シーン管理用
	enum class SCENE_ID
	{
		NONE = 0,
		TITLE = 1,
		TRAIN = 2,
		GAME = 3,
		BOSS = 4,
		RESULT = 5,
		GAMEOVER = 6,
		ABILITYROOM = 7,
	};

	/// <summary>
	/// 初期化
	/// </summary>
	void Init();

	/// <summary>
	/// 3D関連の初期化
	/// </summary>
	void Init3D();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// リソースの破棄
	/// </summary>
	void Release() const;

	/// <summary>
	/// 先頭の（Updateが呼ばれる）シーンを切り替える
	/// </summary>
	/// <param name="scene">切り替え先のシーン</param>
	void CreateScene(const std::shared_ptr<SceneBase>& scene);

	/// <summary>
	/// シーンをプッシュする。スタックの数が増える
	/// 一番上のシーンのUpdateしか呼ばれません。
	/// </summary>
	/// <param name="scene">積むシーン</param>
	void PushScene(const std::shared_ptr<SceneBase>& scene);

	/// <summary>
	/// スタックの頭のシーンを削除する。
	/// ただし、スタック上にシーンが一つしかない場合は、削除しない。
	/// </summary>
	void PopScene();

	/// <summary>
	/// サブシーンの生成準備
	/// </summary>
	/// <param name="subScene">サブシーン</param>
	void SetReadySubScene(const std::shared_ptr<SceneBase> subScene);

	/// <summary>
	/// シーン遷移
	/// </summary>
	/// <param name="nextId">変更先のシーン</param>
	void ChangeScene(const SCENE_ID nextId, const Fader::STATE fadeState = Fader::STATE::FADE_OUT);
	
	/// <summary>
	/// フェードを始める
	/// </summary>
	void StartFadeIn(const Fader::STATE fadeState = Fader::STATE::FADE_IN);

	/// <summary>
	/// スクリーン座標
	/// </summary>
	/// <param name="pos">スクリーン座標</param>
	void SetScreenPos(const Vector2& pos) { screenPos_ = pos; }

	/// <summary>
	/// ヒットストップを設定
	/// </summary>
	/// <param name="hitStopTime">ヒットストップ時間</param>
	void SetHitStop(const float hitStopTime) { hitStopTimer_ = hitStopTime; }

	/// <summary>
	/// メインスクリーンを返す
	/// </summary>
	/// <returns>メインスクリーン</returns>
	const int GetMainScreen() const { return mainScreen_; }

	/// <summary>
	/// 現在のシーンIDを返す
	/// </summary>
	/// <returns>現在のシーンID</returns>
	const SCENE_ID GetSceneID() const { return sceneId_; }

	/// <summary>
	/// デルタタイムを返す
	/// </summary>
	/// <returns>デルタタイム</returns>
	const float GetDeltaTime() const { return deltaTime_; }

	/// <summary>
	/// 経過時間を返す
	/// </summary>
	/// <returns>経過時間</returns>
	const float GetTotalTime() const { return totalTime_; }

	/// <summary>
	/// カメラを返す
	/// </summary>
	/// <returns>カメラ</returns>
	Camera& GetCamera() { return *camera_; }

	/// <summary>
	/// ショップシーンを返す
	/// </summary>
	/// <returns>ショップシーン</returns>
	const std::shared_ptr<SceneShop> GetSceneShop() const { return sceneShop_; }

	/// <summary>
	/// ショップ画面の設定
	/// </summary>
	void SetShopScene(const Input::JOYPAD_NO padNo);

	void ResetPausePadNo() { pausePadNo_ = -1; }

private:

	// シーンID
	SCENE_ID sceneId_;
	SCENE_ID waitSceneId_;

	// 各種シーン
	std::list<std::shared_ptr<SceneBase>> scenes_;

	// フェード
	std::unique_ptr<Fader> fader_;

	// カメラ
	std::unique_ptr<Camera> camera_;

	// サブシーン受け取り用
	std::shared_ptr<SceneBase> subScene_;

	// ショップ
	std::shared_ptr<SceneShop> sceneShop_;

	// スクリーン座標
	Vector2 screenPos_;

	// メインスクリーン
	int mainScreen_;

	// シーン遷移中判定
	bool isSceneChanging_;

	// ヒットストップ用タイマー
	float hitStopTimer_;

	// デルタタイム
	std::chrono::system_clock::time_point preTime_;
	float deltaTime_;

	//経過時間
	float totalTime_;

	// ポーズ、ポーズしているコントローラー判定に使用
	int pausePadNo_;
	
	// デフォルトコンストラクタをprivateにして、
	// 外部から生成できない様にする
	SceneManager();

	// デストラクタも同様
	~SceneManager() = default;

	// デルタタイムをリセットする
	void ResetDeltaTime();

	// シーン遷移
	void DoChangeScene(SCENE_ID sceneId);

	// フェード
	void Fade();
};