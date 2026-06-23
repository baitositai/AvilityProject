#pragma once
#include "../UiBase.h"

class UiGameBase : public UiBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	UiGameBase();

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~UiGameBase() override;

	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw() override;

protected:

	// 描画する数字
	int drawCount_;

	// 数字画像ハンドル
	int* numberHandle_;

	// 数字の拡大率
	float numberScale_;

	// 数字描画開始位置
	Vector2 numberStartDrawPos_;

	// 数字サイズ
	Vector2 numberSize_;

	// 数字の初期化
	void InitNumber();

	// 数字の描画
	void DrawNumber();
};

