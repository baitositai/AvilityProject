#pragma once
#include <functional>
#include "../UiBase.h"

class SceneManager;

class UiTrainTime : public UiBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	UiTrainTime();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~UiTrainTime() override;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() override;

private:

	// 拡大時間
	static constexpr float SCALE_UP_TIME = 0.5f;

	// 拡大目標値
	static constexpr float SCALE_GOAL = 1.0f;

	// 待機時間
	static constexpr float WAIT_TIME = 1.5f;

	// 透過減衰速度
	static constexpr float ALPHA_SUB_SPEED = 5.0f;

	// 透過値
	float alpha_;

	// タイマー
	float timer_;

	// シーン管理クラス
	SceneManager& sceneManager_;

	// 更新処理
	std::function<void()> update_;

	void UpdateScale();
	void UpdateWait();
	void UpdateExit();
};