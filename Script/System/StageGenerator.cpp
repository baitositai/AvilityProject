#include <algorithm>
#include <random>
#include <fstream>
#include "../../Application.h"
#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Common/Camera.h"
#include "../../Common/Vector2F.h"
#include "../../Utility/UtilityLoad.h"
#include "StageGenerator.h"

StageGenerator::StageGenerator()
{
}

StageGenerator::~StageGenerator()
{
}

std::vector<std::vector<int>> StageGenerator::CreateStageData(const Parameter& parameter)
{
	std::vector<std::vector<int>> result;

	if (parameter.connectNum <= 0)
	{
		return result;
	}

	// 候補リストを複製してランダムにシャッフルするための準備をします
	std::vector<std::string> shuffledCandidates = parameter.candidates;

	// ランダムデバイスを利用して候補リストの順番を並び替えます
	std::random_device seedGenerator;
	std::mt19937 randomEngine(seedGenerator());
	std::shuffle(shuffledCandidates.begin(), shuffledCandidates.end(), randomEngine);

	std::vector<std::string> workPath;
	std::vector<std::string> selectedNames;

	// シャッフルした候補リストを渡すことでランダムな接続ルートを探索します
	bool hasFound = FindConnectPath(shuffledCandidates, parameter.connectNum, workPath, selectedNames);

	if (!hasFound)
	{
		return result;
	}

	std::vector<std::vector<std::vector<int>>> selectedMatrices;

	// カメラのスクロール設定
	SetCameraScroll(selectedNames);

	// 確定した接続ルートの名前からCSVデータを順番に読み込みます
	for (const auto& name : selectedNames)
	{
		// ファイル名として配列の名前をそのまま渡してデータをロードします
		std::vector<std::vector<int>> currentMatrix = UtilityLoad::LoadCSVData("StageChip" + name);
		selectedMatrices.push_back(currentMatrix);
	}

	// ロードしたすべての2次元配列を1つに結合して返します
	return CombineMatrixList(selectedMatrices);
}

std::vector<std::vector<int>> StageGenerator::LoadCreateStageData(const std::string& stagePath)
{
	return UtilityLoad::LoadCSVData(stagePath);
}

bool StageGenerator::FindConnectPath(const std::vector<std::string>& candidates, const int targetCount, std::vector<std::string>& currentPath, std::vector<std::string>& outResult)
{
	// 指定された接続数に達した場合の判定処理です
	int currentPathSize = static_cast<int>(currentPath.size());
	if (currentPathSize == targetCount)
	{
		// 最後の要素の末尾がGであれば探索成功とみなします
		if (!currentPath.empty() && currentPath.back().back() == 'G')
		{
			outResult = currentPath;
			return true;
		}
		return false;
	}

	// 最後の1個を接続するときの判定処理です
	currentPathSize = static_cast<int>(currentPath.size());
	if (currentPathSize == targetCount - 1)
	{
		char requiredPrefix = currentPath.back().back();
		for (const auto& word : candidates)
		{
			// 末尾がGでありかつ前の要素の末尾と頭文字が一致するものを選びます
			if (word.back() == 'G' && word.front() == requiredPrefix)
			{
				currentPath.push_back(word);
				if (FindConnectPath(candidates, targetCount, currentPath, outResult))
				{
					return true;
				}
				currentPath.pop_back();
			}
		}
		return false;
	}

	// 道中の要素を接続するときのループ処理です
	for (const auto& word : candidates)
	{
		// 途中でGが末尾の要素が入ることは禁止します
		if (word.back() == 'G')
		{
			continue;
		}

		// 一番最初の要素を選ぶときの処理です
		if (currentPath.empty())
		{
			// 頭文字がSの要素から開始します
			if (word.front() == 'S')
			{
				currentPath.push_back(word);
				if (FindConnectPath(candidates, targetCount, currentPath, outResult))
				{
					return true;
				}
				currentPath.pop_back();
			}
		}
		// 2個目以降の要素を選ぶときの処理です
		else
		{
			char requiredPrefix = currentPath.back().back();
			// 前の要素の末尾と次の要素の頭文字が一致しているか判定します
			if (word.front() == requiredPrefix)
			{
				currentPath.push_back(word);
				if (FindConnectPath(candidates, targetCount, currentPath, outResult))
				{
					return true;
				}
				currentPath.pop_back();
			}
		}
	}

	return false;
}

std::vector<std::vector<int>> StageGenerator::CombineMatrixList
(
	const std::vector<std::vector<std::vector<int>>>& sourceLists
)
{
	std::vector<std::vector<int>> combinedResult;

	if (sourceLists.empty() || sourceLists[0].empty())
	{
		return combinedResult;
	}

	int rowCount = static_cast<int>(sourceLists[0].size());
	combinedResult.resize(static_cast<size_t>(rowCount));

	for (int rowIndex = 0; rowIndex < rowCount; ++rowIndex)
	{
		int totalColumns = 0;
		for (const auto& matrix : sourceLists)
		{
			if (rowIndex < static_cast<int>(matrix.size()))
			{
				totalColumns += static_cast<int>(matrix[static_cast<size_t>(rowIndex)].size());
			}
		}
		combinedResult[static_cast<size_t>(rowIndex)].reserve(static_cast<size_t>(totalColumns));

		for (const auto& matrix : sourceLists)
		{
			if (rowIndex < static_cast<int>(matrix.size()))
			{
				combinedResult[static_cast<size_t>(rowIndex)].insert
				(
					combinedResult[static_cast<size_t>(rowIndex)].end(),
					matrix[static_cast<size_t>(rowIndex)].begin(),
					matrix[static_cast<size_t>(rowIndex)].end()
				);
			}
		}
	}

	return combinedResult;
}

void StageGenerator::SetCameraScroll(const std::vector<std::string>& paths)
{
	// ファイルを直接ストリームとして開く
	std::ifstream file(Application::PATH_JSON + "StageChips.json");
	if (!file.is_open())
	{
		return;
	}

	// jsonオブジェクトにパース
	nlohmann::json stageChipsJson;
	file >> stageChipsJson;

	std::vector<Vector2F> moveList = {};
	for (auto& path : paths)
	{
		// ルートオブジェクトに指定のステージチップのキーが存在するかチェック
		if (stageChipsJson.find(path) == stageChipsJson.end())
		{
			continue;
		}

		auto& chipDataJson = stageChipsJson[path];

		// チップデータの中に cameraMove が存在するかチェック
		if (chipDataJson.find("cameraMove") == chipDataJson.end())
		{
			continue;
		}

		auto& cameraMovesJson = chipDataJson["cameraMove"];

		// 配列であることを確認してループ処理
		if (cameraMovesJson.is_array())
		{
			for (auto& moveData : cameraMovesJson)
			{
				float x = moveData["x"].get<float>();
				float y = moveData["y"].get<float>();

				moveList.push_back(Vector2F(x, y));
			}
		}

		// チップデータの中に firstPosYOffset が存在するかチェック
		if (chipDataJson.find("firstPosYOffset") == chipDataJson.end())
		{
			continue;
		}

		// カメラ初期位置の格納
		Vector2F pos = {};
		pos.y = chipDataJson["firstPosYOffset"].get<float>();
		mainCamera.SetCameraPos(pos);
	}
	
	// 移動量の設定
	mainCamera.SetCameraScrollMove(moveList);
}
