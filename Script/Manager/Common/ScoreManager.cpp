#include "ScoreManager.h"

void ScoreManager::AddScore(const int score)
{
	// スコアを追加
	score_ += score;

	// スコアが0未満の場合は0にする
	if (score_ < 0)
	{
		score_ = 0;
	}
}

void ScoreManager::AddTotalScore(const int score)
{
	totalScore_ += score;
	if (totalScore_ < 0)
	{
		totalScore_ = 0;
	}
}

void ScoreManager::AddTotalScore()
{
	totalScore_ += score_;
}

void ScoreManager::Clear()
{
	totalScore_ = 0;
	score_ = 0;
}

void ScoreManager::Handover()
{
	totalScore_ += score_;
	score_ = 0;
}

ScoreManager::ScoreManager()
{
	totalScore_ = 0;
	score_ = 0;
}
