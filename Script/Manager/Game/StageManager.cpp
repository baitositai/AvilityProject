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

	//AvilityBox::Parameter avParam = {};
	//avParam.hitBoxSize = Vector2(48, 48);
	//avParam.pos = Vector2F(300, 400);
	//avParam.gravityPower = 0.5f;
	//avParam.weight = 0.8f;
	//avParam.blastTime = 3.0f;
	//std::vector<std::string> componentNameList = { "gravity","move"};
	//std::unique_ptr avBox = std::make_unique<AvilityBox>(avParam);
	//gimmick_=std::make_unique<AvilityBox>(avParam, componentNameList);
	//gimmick_->Init();
	//for (const auto& gim : gimmick_)
	//{
	//	gim->Init();
	//}
}

void StageManager::Update()
{
	stage_->Update();
	//gimmick_->Update();
	for (const auto& gim : gimmick_)
	{
		gim->Update();
	}
	GimmickSweep();
}

void StageManager::Draw()
{
	stage_->Draw();
	//gimmick_->Draw();
	for (const auto& gim : gimmick_)
	{
		gim->Draw();
	}
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
	//gimmick_->DebugDraw();
	for (const auto& gim : gimmick_)
	{
		gim->DebugDraw();
	}
}

void StageManager::AddGimmick(const Vector2F& _charaPos, const bool _direction)
{
	AvilityBox::Parameter avParam = {};
	avParam.hitBoxSize = Vector2(48, 48);
	avParam.gravityPower = 0.5f;
	avParam.weight = 0.8f;
	avParam.blastTime = 3.0f;

	//ローカル座標をJsonで読み込み、プレイヤーの向きによって設置場所を変える
	Vector2F localPos = { 50.0f,50.0f };
	avParam.placePos= _direction? Vector2F::SubVector2F(_charaPos, localPos): Vector2F::AddVector2F(_charaPos, localPos);
	std::vector<std::string> componentNameList = { "gravity","move" };

	//いったんアビリティボックスのみ対応
	std::unique_ptr avBox = std::make_unique<AvilityBox>(avParam, _charaPos, componentNameList);
	avBox->Init();
	gimmick_.push_back(std::move(avBox));
}

void StageManager::DeleteGimmick(void)
{
	//一番古いギミックを消す
	gimmick_.back()->SetIsDelete();
}

void StageManager::GimmickSweep()
{
	auto removeGim = std::remove_if(gimmick_.begin(), gimmick_.end(), [](std::unique_ptr<GimmickBase>& _gim)
		{
			return _gim->IsDelete();
		});
	gimmick_.erase(removeGim, gimmick_.end());
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