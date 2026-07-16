#pragma once
#include "../UiBase.h"

class UiTimer : public UiBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	UiTimer();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~UiTimer() override;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() override;

	/// <summary>
	/// 数字の設定
	/// </summary>
	/// <param name="number">数字</param>
	void SetNumber(const int number);

	/// <summary>
	/// パラメーター値の設定
	/// </summary>
	/// <param name="pos">描画中心位置</param>
	/// <param name="drawCount">描画番号</param>
	/// <param name="scale">拡大率</param>
	void SetParameter(const Vector2& pos, const int drawCount = 0, const float scale = 1.0f);

private:

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
	Vector2 defaultNumberSize_;

};