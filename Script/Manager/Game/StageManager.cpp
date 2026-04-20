#include <algorithm>
#include "../../Application.h"
#include "../../Utility/UtilityLoad.h"
#include "../../Object/Stage/Stage.h"
#include "../Common/Camera.h"
#include "../Common/SceneManager.h"
#include "StageManager.h"

void StageManager::Init()
{
	// メインステージ
	Stage::StageParameter parameter = {};
	parameter.path = STAGE_PATH_MAP.at(type_);
	parameter.chipSize = Vector2(32, 32);
	parameter.hitIds = { 1 };
	stage_ = std::make_unique<Stage>(parameter);
	stage_->Init();
}

void StageManager::Update()
{
	stage_->Update();
}

void StageManager::Draw()
{
	stage_->Draw();
}

void StageManager::ChageStage(const TYPE type)
{
	type_ = type;
	stage_->ChageStage(STAGE_PATH_MAP.at(type_));
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

const Vector2& StageManager::GetStageSize() const
{
	return stage_->GetStageSize();
}

StageManager::StageManager()
{
	type_ = TYPE::NONE;
}

StageManager::~StageManager()
{
}