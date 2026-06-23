#pragma once
#include "UiGameBase.h"

class ScoreManager;
class SceneManager;

class UiMoney : public UiGameBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	UiMoney();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~UiMoney() override;

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

	// スコア管理クラス
	ScoreManager& scoreManager_;

	// シーン管理クラス
	SceneManager& sceneManager_;
};