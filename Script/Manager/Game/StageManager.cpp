#include <algorithm>
#include "../../Application.h"
#include "../../Utility/UtilityLoad.h"
#include "../../Object/Stage/Stage.h"
#include "../../Object/Gimmick/AvilityBox.h"
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

	AvilityBox::Parameter avParam = {};
	avParam.hitBoxSize = Vector2(100, 100);
	avParam.pos = Vector2F(300, 400);
	avParam.gravityPower = 0.1f;
	avParam.weight = 0.1f;
	std::vector<std::string> componentNameList = { "gravity","move"};
	//std::unique_ptr avBox = std::make_unique<AvilityBox>(avParam);
	gimmick_=std::make_unique<AvilityBox>(avParam, componentNameList);
	gimmick_->Init();
	//for (const auto& gim : gimmick_)
	//{
	//	gim->Init();
	//}
}

void StageManager::Update()
{
	stage_->Update();
	gimmick_->Update();
	//for (const auto& gim : gimmick_)
	//{
	//	gim->Update();
	//}
}

void StageManager::Draw()
{
	stage_->Draw();
	gimmick_->Draw();
	//for (const auto& gim : gimmick_)
	//{
	//	gim->Draw();
	//}
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
	gimmick_->DebugDraw();
	//for (const auto& gim : gimmick_)
	//{
	//	gim->DebugDraw();
	//}
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