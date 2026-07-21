#pragma once
#include <string>
#include <unordered_map>
#include "SceneBase.h"

#include "../Manager/Common/InputManager.h"

class ScenePause : public SceneBase
{
public:

	//ポーズリスト
	enum class LIST
	{
		RESUME,		// 続ける
		NONE,		// なし
		TITLE,		// タイトルに戻る
		GAME_END,   // ゲームの終了
		MAX
	};

	//リスト
	static constexpr int LIST_MAX = static_cast<int>(LIST::MAX);

	// コンストラクタ
	ScenePause();
	ScenePause(Input::JOYPAD_NO PadNo);

	// デストラクタ
	~ScenePause() override;

	//読み込み処理
	void Load() override {};

	//初期化処理
	void Init() override {};

	//更新関数
	void NormalUpdate() override;

	//描画関数
	void NormalDraw() override;

private:
	
	//画面のアルファ値
	static constexpr int PAUSE_ALPHA = 196; // 64,128,196

	//フォントサイズ
	static constexpr int FONT_SIZE = 56;
	static constexpr int FONT_THICK = 3; // フォントの太さ

	//ポーズフォント
	int pauseFont_; 	

	//ポーズリストの選択
	int selectIndex_;

	//選択リスト
	std::wstring pasueList_[LIST_MAX] =
	{
		L"つづける",
		L"NONE",
		L"タイトルへ戻る",
		L"ゲーム終了"
	};

	int* handleIds_;

	//リスト選択テーブル
	std::unordered_map<LIST, std::function<void()>> listFuncTable_;

	// 操作プレイヤーコントローラー
	Input::JOYPAD_NO PadNo_;
};

