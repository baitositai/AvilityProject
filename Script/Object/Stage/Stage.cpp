#include <algorithm>
#include "../../Application.h"
#include "../../Utility/UtilityLoad.h"
#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Common/Camera.h"
#include "../../Collider/ColliderArray.h"
#include "../../OnHit/OnHitBase.h"
#include "Tile/TileBase.h"
#include "Stage.h"

Stage::Stage(StageParameter& parameter) :
	 parameter_(parameter),
	ActorBase(&parameter_)
{
	stageSize_ = {};
	tileNums_ = {};	
}

Stage::~Stage()
{
}

void Stage::Init()
{
	// コライダーの生成
	collider_ = std::make_unique<ColliderArray>(*this, CollisionTags::TAG::STAGE, chipIndexs_, parameter_.hitIds, parameter_.chipSize);

	// 衝突後処理
	onHit_ = nullptr;

	// タイルの初期化
	for (const auto& tileRow : tiles_)
	{
		for (const auto& tile : tileRow)
		{
			tile->Init();
		}
	}

	// 基底クラスの処理
	ActorBase::Init();
}

void Stage::Update()
{
}

void Stage::Draw()
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

void Stage::ChageStage(const std::string& stagePath)
{
	// 種類の定義
	parameter_.path = stagePath;

	// ステージの設定
	SetStage();
}

void Stage::DebugDraw()
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

void Stage::SetStage()
{
	// タイルの読み込み
	chipIndexs_ = UtilityLoad::LoadCSVData(Application::PATH_CSV + parameter_.path);

	// ステージの初期化
	ClearStage();

	// タイルの生成
	for (size_t y = 0; y < chipIndexs_.size(); y++)
	{
		std::vector<std::unique_ptr<TileBase>> tileRow;
		for (size_t x = 0; x < chipIndexs_[y].size(); x++)
		{
			// タイルのパラメータを設定
			TileBase::Parameter parameter;
			parameter.id = chipIndexs_[y][x];
			parameter.type = static_cast<TileBase::TYPE>(chipIndexs_[y][x]);
			parameter.position = Vector2(static_cast<int>(x * TileBase::SIZE_TILE), static_cast<int>(y * TileBase::SIZE_TILE));
			tileRow.push_back(std::make_unique<TileBase>(parameter));
		}
		tiles_.push_back(std::move(tileRow));
	}

	// タイル数の設定
	tileNums_.x = static_cast<int>(chipIndexs_[0].size());
	tileNums_.y = static_cast<int>(chipIndexs_.size());

	// ステージの幅と高さの設定
	stageSize_.x = tileNums_.x * TileBase::SIZE_TILE;
	stageSize_.y = tileNums_.y * TileBase::SIZE_TILE;

	// コライダーの情報も再登録
	auto colliderArray = std::dynamic_pointer_cast<ColliderArray>(collider_);
	if (colliderArray == nullptr) return;
	colliderArray->SetArrayOfArrays(chipIndexs_);
}

void Stage::ClearStage()
{
	// タイルの配列が空の場合
	if (tiles_.empty())
	{
		return;
	}

	// タイルの配列をクリア
	tiles_.clear();
}

void Stage::GetDrawRange(Vector2& rangeMin, Vector2& rangeMax)
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