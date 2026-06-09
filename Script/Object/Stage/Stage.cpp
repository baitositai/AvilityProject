#include <algorithm>
#include <DxLib.h>
#include "../../Application.h"
#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Common/Camera.h"
#include "../../Manager/Common/ResourceManager.h"
#include "../../Manager/Game/CollisionManager.h"
#include "../../Utility/UtilityLoad.h"
#include "../../Utility/UtilityCommon.h"
#include "../../Collider/ColliderArray.h"
#include "../../OnHit/OnHitBase.h"
#include "../Common/Animation.h"
#include "Tile/TileBase.h"
#include "Stage.h"

Stage::Stage(std::unique_ptr<ParameterStage> parameter) :
	ActorBase(std::move(parameter))
{	
	stageSize_ = {};
	tileNums_ = {};

	// パラメータ
	parameterStage_ = dynamic_cast<ParameterStage*>(GetParameterActorPtr());
	assert(parameterStage_ != nullptr);
}

Stage::~Stage()
{
}

void Stage::Init()
{
	// コライダーの生成
	auto collider = std::make_shared<ColliderArray>(
		*this, 
		CollisionTags::TAG::STAGE,
		parameterStage_->pos_, 
		parameterStage_->tileIndexs_,
		parameterStage_->chipSize_);

	// ステージ専用のコライダーの設定
	CollisionManager::GetInstance().SetStageCollider(collider);	
	
	// 保持用に格納
	collider_ = collider;

	// 衝突後処理
	onHit_ = nullptr;

	// ステージ設定
	SetStage();

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
	if(!stagePath.empty())
	{
		parameterStage_->tileIndexs_.clear();
		parameterStage_->tileIndexs_ = UtilityLoad::LoadCSVData(Application::PATH_CSV + stagePath);
	}

	// ステージの設定
	SetStage();
}

void Stage::DebugDraw()
{
	Vector2 rangeMin, rangeMax;
	GetDrawRange(rangeMin, rangeMax);

	for (int i = rangeMin.x; i < rangeMax.x; i++)
	{
		for (int j = rangeMin.y; j < rangeMax.y; j++)
		{
			tiles_[j][i]->DebugDraw();
		}
	}

	Vector2F pos = mainCamera.GetPos();

	//const auto& enemyCreateAreaList = areaListMap_.at(LIST_TYPE::ENEMY_CREATE_AREA);
	//if (enemyCreateAreaList.empty()) return;

	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
	//// 敵の生成位置を可視化
	//for (const auto& enemySpawnArea : enemyCreateAreaList)
	//{
	//	DrawBox(
	//		pos.x + enemySpawnArea.x - 64,
	//		pos.y + enemySpawnArea.y - 32,
	//		pos.x + enemySpawnArea.x + 64,
	//		pos.y + enemySpawnArea.y + 32,
	//		UtilityCommon::YELLOW,
	//		true
	//	);
	//}
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Stage::SetStage()
{
	// ステージの初期化
	ClearStage();

	// テクスチャ取得
	int* handles = resMng_.GetHandles(parameterStage_->resourceKey_);

	// タイルの生成
	for (size_t y = 0; y < parameterStage_->tileIndexs_.size(); y++)
	{
		std::vector<std::unique_ptr<TileBase>> tileRow;
		for (size_t x = 0; x < parameterStage_->tileIndexs_[y].size(); x++)
		{
			// タイルのパラメータを設定
			TileBase::Parameter parameter;
			parameter.handle = -1 < parameterStage_->tileIndexs_[y][x] ? handles[parameterStage_->tileIndexs_[y][x]] : -1;
			parameter.id = parameterStage_->tileIndexs_[y][x];
			parameter.type = static_cast<TileBase::TYPE>(parameterStage_->tileIndexs_[y][x]);
			parameter.position = Vector2(static_cast<int>(x * TileBase::SIZE_TILE), static_cast<int>(y * TileBase::SIZE_TILE));
			tileRow.push_back(std::make_unique<TileBase>(parameter));
		}
		tiles_.push_back(std::move(tileRow));
	}

	// タイル数の設定
	tileNums_.x = static_cast<int>(parameterStage_->tileIndexs_[0].size());
	tileNums_.y = static_cast<int>(parameterStage_->tileIndexs_.size());

	// ステージの幅と高さの設定
	stageSize_.x = tileNums_.x * TileBase::SIZE_TILE;
	stageSize_.y = tileNums_.y * TileBase::SIZE_TILE;

	// コライダーの情報も再登録
	auto colliderArray = std::dynamic_pointer_cast<ColliderArray>(collider_);
	if (colliderArray == nullptr) return;
	colliderArray->SetArrayOfArrays(parameterStage_->tileIndexs_);

	if (!areaListMap_.empty())
	{
		areaListMap_.clear();
	}

	// 生成リストの登録
	for (int y = 0; y < tileNums_.y; y++)
	{
		for (int x = 0; x < tileNums_.x; x++)
		{
			// 指定外のインデックスの場合
			if (-1 <= parameterStage_->tileIndexs_[y][x])
			{
				// 次へ
				continue;
			}
			for (int i = 0; i < LIST_TYPE_MAX; i++)
			{
				// 指定のインデックスと一致してる場合
				if (LIST_TYPE_INDEXS[i] == parameterStage_->tileIndexs_[y][x])
				{
					// 登録
					areaListMap_[static_cast<LIST_TYPE>(i)].push_back(
						Vector2(x * parameterStage_->chipSize_.x, y * parameterStage_->chipSize_.y).ToVector2F());
					break;
				}
			}
		}
	}
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

const std::vector<Vector2F>& Stage::GetAreaListMap(const LIST_TYPE type) const
{
	return areaListMap_.at(type);
}