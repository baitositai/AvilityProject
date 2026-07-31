#pragma once
#include <functional>
#include <unordered_map>
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

	//メニューイージングパラメータ
	struct EasingParameter
	{
		float easeCnt = 0.0f;
		Vector2 startPos;
		Vector2 goalPos;
		bool isEasing = false;
		bool isEndEase = false;
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

	//タイトルイージング時間
	static constexpr float TITLE_EASE_TIME = 1.0f;
	//タイトルの出てくる間隔時間
	static constexpr float MENU_SPAWN_DISTIME = 0.1f;
	//タイトルのイージング時間
	static constexpr float MENU_EASE_TIME = 0.5f;

	//メニュー名のイージング時間
	static constexpr float MENU_NAME_EASE_TIME = 1.5f;
	//ボタン説明のイージング時間
	static constexpr float MENU_EXPLANATIONS_NAME_EASE_TIME = 1.5f;

	//粘土細工のイージング時間
	static constexpr float CLAYWORK_EASE_TIME = 5.0f;

	//花形イージングのパラメーター
	static constexpr float HALF_RADIUS_NUM = 5.0f;
	static constexpr float SMALL_RADIUS = 5.0f;

	//矢印座標のイージング始端位置のローカルY
	static constexpr float ARROW_EASE_LOCAL_Y = 20.0f;

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
	EasingParameter uiMenuEaseParam_;

	// 説明
	Sprite uiExplanations_;
	EasingParameter uiExplanationsEaseParam_;

	//ねんど細工の画像
	Image arrow_;
	EasingParameter arrowEaseParam_;

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

	//タイトルイージングカウント
	float titleEaseCnt_;
	//タイトルイージング開始座標
	float titleLogoStartPosX_;
	
	//メニューが出てくる間隔
	float menuSpawnDisCount_;
	std::array<EasingParameter, MENU_COUNT_MAX>menuEasingParams_;

	// 更新関数
	void NormalUpdate() override;

	// 描画関数
	void NormalDraw() override;

	//メニューを動かす
	void EaseMenuButton(const int menuNum);

	//メニュー名と説明のイージング
	void EaseMenuAndExplanations(void);

	// 更新処理
	void UpdateMain();
	void UpdateEaseTitle();
	void UpdateEaseTitleBack();
	void UpdateSelect();
	void UpdateSelectEase();
	void UpdateSelectEaseBack();

	// 描画処理
	void DrawMain();
	void DrawSelect();

	// メニュー遷移処理
	void ChangeMenuGame();
	void ChangeMenuTutorial();
	void ChangeMenuAbilityTrial();
	void ChangeMenuBack();
};