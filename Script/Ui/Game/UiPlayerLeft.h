#pragma once
#include "UiGameBase.h"

class PlayerManager;

class UiPlayerLeft : public UiGameBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	UiPlayerLeft();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~UiPlayerLeft() override;

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

	// 数字ハンドル
	int* numberHandle_;

	// プレイヤー管理クラス
	PlayerManager& playerManager_;

};