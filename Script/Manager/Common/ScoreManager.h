#pragma once
#include "../../Template/Singleton.h"

class ScoreManager : public Singleton<ScoreManager>
{
	//シングルトンにだけ共有する
	friend class Singleton<ScoreManager>;

public:

	/// <summary>
	/// スコアを返す
	/// </summary>
	/// <returns>スコア</returns>
	const int GetScore() const { return score_; }

	/// <summary>
	/// 合計スコアを返す
	/// </summary>
	/// <returns></returns>
	const int GetTotalScore() const { return totalScore_; }

	/// <summary>
	/// スコアの追加
	/// </summary>
	/// <param name="score">スコア</param>
	void AddScore(const int score);

	/// <summary>
	/// 合計スコアに加算
	/// </summary>
	/// <param name="score">加算スコア</param>
	void AddTotalScore(const int score);

	/// <summary>
	/// 合計スコアに追加
	/// </summary>
	void AddTotalScore();

	/// <summary>
	/// スコアを0にする
	/// </summary>
	void DeadScore() { score_ = 0; }

	/// <summary>
	/// クリア処理
	/// </summary>
	void Clear();

	/// <summary>
	/// スコア引継ぎ
	/// </summary>
	void Handover();

private:

	// ゲームスコア
	int score_;

	// 合計スコア
	int totalScore_;

	// コンストラクタ
	ScoreManager();

	// デストラクタ
	~ScoreManager() = default;
};