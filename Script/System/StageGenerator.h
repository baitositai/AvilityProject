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

	// 接続するパスを探す
	bool FindConnectPath(
		const std::vector<std::string>& candidates, 
		const int targetCount, 
		std::vector<std::string>& currentPath, 
		std::vector<std::string>& outResult);

	// 配列をつなげる
	std::vector<std::vector<int>> CombineMatrixList(const std::vector<std::vector<std::vector<int>>>& sourceLists);

	// カメラスクロールの設定
	void SetCameraScroll(const std::vector<std::string>& path);
};

