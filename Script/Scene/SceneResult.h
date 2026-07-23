#pragma once
#include "SceneBase.h"
#include "../Common/Image.h"
#include "../Common/CharacterString.h"

class SceneResult : public SceneBase
{
public:

	//ポーズリスト
	enum class LIST
	{
		RESUME,		// 続ける
		TITLE,		// タイトルに戻る
		MAX
	};

	//リスト
	static constexpr int LIST_MAX = static_cast<int>(LIST::MAX);

	/// <summary>
	/// コンストラクタ
	/// </summary>
	SceneResult();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SceneResult() override;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

private:

	//ポーズリストの選択
	int selectIndex_;

	//リスト選択テーブル
	std::unordered_map<LIST, std::function<void()>> listFuncTable_;
	std::unordered_map<LIST, Image> listImage_;

	// 変動用スコア
	float score_;

	// スコア画像
	int* handleIds_;
	Image gold_; 

	Image rank_;
	Image result_;
	Image totalScoreEarned_;

	// 演出時間
	float resulTime_;

	// 背景
	std::unique_ptr<BackGround> backGround_[9];

	// 地面
	std::unique_ptr<BackGround> ground_;

	// 更新関数
	void NormalUpdate() override;
	void SecondUpdate();

	// 描画関数
	void NormalDraw() override;
	void SecondDraw();

	void ScoreDraw();
};