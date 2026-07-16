#pragma once
#include "./UiGameBase.h"
class UIButtonExpand : public UiGameBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">所有者</param>
	UIButtonExpand();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~UIButtonExpand() override;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

private:

	//ボタン座標
	static constexpr int BUTTON_EXPAND_POS_X = 1150;
	static constexpr int BUTTON_EXPAND_POS_Y = 80;
};

