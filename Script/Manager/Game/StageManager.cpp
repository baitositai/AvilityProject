#include <algorithm>
#include "../../Application.h"
#include "../../Utility/UtilityLoad.h"
#include "../../Object/Tile/TileBase.h"
#include "../Common/Camera.h"
#include "../Common/SceneManager.h"
#include "StageManager.h"

void StageManager::Init()
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

void StageManager::Update()
{
}

void StageManager::Draw()
{
	// 描画範囲の取得
	Vector2 rangeMin, rangeMax;
	GetDrawRange(rangeMin, rangeMax);

	for (int i = rangeMin.x; i < rangeMax.x; i++)
	{
		for (int j = rangeMin.y; j < rangeMax.y; j++)
		{
			tiles_[j][i]->Draw();
		}
	}
}

void StageManager::ChageStage(const TYPE type)
{
	// 種類の定義
	type_ = type;

	// ステージの設定
	SetStage();
}

void StageManager::DebugDraw()
{
	// タイルの仮描画
	/*for (int i = 0; i < tileNums_.x; i++)
	{
		for (int j = 0; j < tileNums_.y; j++)
		{
			tiles_[j][i]->DebugDraw();
		}
	}*/
}

void StageManager::SetStage()
{
	// タイルの読み込み
	const std::vector<std::vector<int>> chipIds = UtilityLoad::LoadCSVData(Application::PATH_CSV + STAGE_PATH_MAP.at(type_));

	// ステージの初期化
	ClearStage();

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
			parameter.position = Vector2(static_cast<int>(x * TileBase::SIZE_TILE), static_cast<int>(y * TileBase::SIZE_TILE));
			tileRow.push_back(std::make_unique<TileBase>(parameter));
		}
		tiles_.push_back(std::move(tileRow));
	}

	// タイル数の設定
	tileNums_.x = static_cast<int>(chipIds[0].size());
	tileNums_.y = static_cast<int>(chipIds.size());

	// ステージの幅と高さの設定
	stageSize_.x = tileNums_.x * TileBase::SIZE_TILE;
	stageSize_.y = tileNums_.y * TileBase::SIZE_TILE;
}

void StageManager::ClearStage()
{
	// タイルの配列が空の場合
	if (tiles_.empty())
	{
		return;
	}

	// タイルの配列をクリア
	tiles_.clear();
}

void StageManager::GetDrawRange(Vector2& rangeMin, Vector2& rangeMax)
{
	// カメラの位置を取得
	Vector2F cameraPosF = mainCamera.GetPos();

	// 計算用に整数へキャスト
	int cameraX = std::abs(static_cast<int>(cameraPosF.x));
	int cameraY = std::abs(static_cast<int>(cameraPosF.y));

	// 最小値の計算
	rangeMin.x = cameraX / TileBase::SIZE_TILE;
	rangeMin.y = cameraY / TileBase::SIZE_TILE;

	// 最大値の計算
	rangeMax.x = (cameraX + Application::SCREEN_SIZE_X) / TileBase::SIZE_TILE + 1;
	rangeMax.y = (cameraY + Application::SCREEN_SIZE_Y) / TileBase::SIZE_TILE + 1;

	// 範囲内にクランプ
	rangeMin.x = std::clamp(rangeMin.x, 0, tileNums_.x);
	rangeMin.y = std::clamp(rangeMin.y, 0, tileNums_.y);
	rangeMax.x = std::clamp(rangeMax.x, 0, tileNums_.x);
	rangeMax.y = std::clamp(rangeMax.y, 0, tileNums_.y);
}

StageManager::StageManager()
{
	type_ = TYPE::NONE;
}

StageManager::~StageManager()
{
}
