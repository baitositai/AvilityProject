#pragma once
#include <vector>
#include <string>

class StageGenerator
{
public:

	struct Parameter
	{
		int connectNum = -1;
		std::vector<std::string> candidates = {};
	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	StageGenerator();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~StageGenerator();

	/// <summary>
	/// ステージデータの生成
	/// </summary>
	/// <param name="parameter">パラメータ</param>
	/// <returns>ステージデータを返す</returns>
	std::vector<std::vector<int>> CreateStageData(const Parameter& parameter);

private:

	// 接続する文字列
	const std::vector<std::string> CANDIDATES = {
		"SD", "SC", "SU", "DD", "DC", "DU", "CC", "CD", "CU", "UU", "UC", "UD", "GD", "GC", "GU"
	};

	bool FindConnectPath(
		const std::vector<std::string>& candidates, 
		const int targetCount, 
		std::vector<std::string>& currentPath, 
		std::vector<std::string>& outResult);

	std::vector<std::vector<int>> CombineMatrixList(const std::vector<std::vector<std::vector<int>>>& sourceLists);
};

