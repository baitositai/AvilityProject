#pragma once
#include "../ParameterActor.h"
class ParameterStage : public ParameterActor
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ParameterStage();

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~ParameterStage() override;

	/// <summary>
	/// 読み込み
	/// </summary>
	/// <param name="parameter">パラメータ</param>
	virtual void LoadParameter(const Json& parameter) override;
	
	// 接続数
	int connectNum_;

	// チップサイズ
	Vector2 chipSize_;				
	
	// ステージパス
	std::string path_;				

	// タイル番号の配列
	std::vector<std::vector<int>> tileIndexs_;

	// 接続候補リスト
	std::vector<std::string> candidates_;
};

