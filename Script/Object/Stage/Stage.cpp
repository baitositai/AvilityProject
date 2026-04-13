#include "../Application.h"
#include "../Utility/UtilityLoad.h"
#include "Tile/TileBase.h"
#include "Stage.h"

Stage::Stage(const std::string& path)
{
	// タイルの読み込み
	const std::vector<std::vector<int>> chipIds = UtilityLoad::LoadCSVData(Application::PATH_CSV + path);

	// タイルの生成
	for (size_t y = 0; y < chipIds.size(); y++)
	{
		std::vector<std::unique_ptr<TileBase>> tileRow;
		for (size_t x = 0; x < chipIds[y].size(); x++)
		{
			// タイルのパラメータを設定
			TileBase::Parameter parameter;
			parameter.id = chipIds[y][x];
			parameter.type = static_cast<TileBase::TYPE>(chipIds[y][x]);
			parameter.position = Vector2(static_cast<float>(x * TileBase::SIZE_TILE), static_cast<float>(y * TileBase::SIZE_TILE));
			tileRow.push_back(std::make_unique<TileBase>(parameter));
		}
		tiles_.push_back(std::move(tileRow));
	}
}

Stage::~Stage()
{
}

void Stage::Init()
{
	// タイルの初期化
	for (const auto& tileRow : tiles_)
	{
		for (const auto& tile : tileRow)
		{
			tile->Init();
		}
	}
}

void Stage::Update()
{

}

void Stage::Draw()
{
	const int col = tiles_[0].size();	// 列数
	const int row = tiles_.size();		// 行数

	// タイルの描画
	for (int i = 0; i < col; i++)
	{
		for (int j = 0; j < row; j++)
		{
			tiles_[j][i]->Draw();
		}
	}
}

void Stage::DebugDraw()
{
	const int col = tiles_[0].size();	// 列数
	const int row = tiles_.size();		// 行数

	// タイルの描画
	for (int i = 0; i < col; i++)
	{
		for (int j = 0; j < row; j++)
		{
			tiles_[j][i]->DebugDraw();
		}
	}
}
