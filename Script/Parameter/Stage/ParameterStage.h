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
	~ParameterStage() override;

	/// <summary>
	/// 読み込み
	/// </summary>
	/// <param name="parameter">パラメータ</param>
	void LoadParameter(const Json& parameter) override;
	
	// チップサイズ
	Vector2 chipSize_;				
	
	// ステージパス
	std::string path_;				

	// タイル番号の配列
	std::vector<std::vector<int>> tileIndexs_;
};

