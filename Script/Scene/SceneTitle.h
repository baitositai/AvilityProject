#pragma once
#include <functional>
#include <unordered_map>
#include <array>
#include "../../Common/Image.h"
#include "../../Common/Sprite.h"
#include "SceneBase.h"

class Train;
class BackGround;

class SceneTitle : public SceneBase
{

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	SceneTitle();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SceneTitle() override;

	/// <summary>
	/// 初期化
	/// </summary>
	void Init() override;

private:

	enum class MENU
	{
		START,
		TUTORIAL,
		ABILITY_TRIAL,
		BACK,
	};

	// メニュー数
	static constexpr int MENU_COUNT_MAX = 4;

	// メニュー項目位置
	static constexpr int MENU_POS_X = 950;
	static constexpr int MENU_SELECT_POS_X = 900;
	static constexpr int MENU_POS_Y_START = 120;
	static constexpr int MENU_POS_Y_OFFSET = 130;

	// メニューUI位置
	static constexpr int UI_MENU_POS_X = 275;
	static constexpr int UI_MENU_POS_Y = 180;
	static constexpr int UI_EXPLANATIONS_POS_Y = 300;

	// 選択番号
	int selectMenuIndex_;

	// 透過率
	float alphaRate_;

	// タイトルロゴ
	Image titleLogo_;

	// キー入力
	Image pleaseButton_;

	// メニュー
	Image uiMenu_;

	// 説明
	Sprite uiExplantions_;

	// メニュー画像
	std::array<Image, MENU_COUNT_MAX> menus_;

	// 処理
	std::function<void()> updateTitleFunc_;
	std::function<void()> drawTitleFunc_;
	std::unordered_map<MENU, std::function<void()>> changeMap_;

	// トレイン
	std::unique_ptr<Train> train_;

	// 背景
	std::unique_ptr<BackGround> backGround_[9];

	// 地面
	std::unique_ptr<BackGround> ground_;

	// 更新関数
	void NormalUpdate() override;

	// 描画関数
	void NormalDraw() override;

	// 更新処理
	void UpdateMain();
	void UpdateSelect();

	// 描画処理
	void DrawMain();
	void DrawSelect();

	// メニュー遷移処理
	void ChangeMenuGame();
	void ChangeMenuTutorial();
	void ChangeMenuAbilityTrial();
	void ChangeMenuBack();
};