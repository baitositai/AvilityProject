#include <algorithm>
#include "../../Application.h"
#include "../../Utility/UtilityLoad.h"
#include "../../Object/Character/CharacterBase.h"
#include "../../Object/Stage/BackGround.h"
#include "../../Object/Stage/Stage.h"
#include "../../Object/Gimmick/AvilityBox.h"
#include "../../System/StageGenerator.h"
#include "../Common/Camera.h"
#include "../Common/SceneManager.h"
#include "StageManager.h"

void StageManager::Init()
{
	// ステージジェネレーター用のパラメータ
	StageGenerator::Parameter generatorParameter = {};
	generatorParameter.connectNum = 5;
	generatorParameter.candidates = { "SD", "SC", "SU", "DD", "DC", "DU", "CC", "CD", "CU", "UU", "UC", "UD", "DG", "CG", "UG" };
	auto stageGenerator = std::unique_ptr<StageGenerator>();

	// ステージパラメータ
	std::unique_ptr<ParameterStage> parameter = std::make_unique<ParameterStage>();
	parameter->path_ = STAGE_PATH_MAP.at(type_);
	parameter->chipSize_ = Vector2(32, 32);
	parameter->tileIndexs_ = stageGenerator->CreateStageData(generatorParameter);
	parameter->resourceKey_ = "groundChipsDungeon";

	// ステージ生成
	stage_ = std::make_unique<Stage>(std::move(parameter));
	stage_->Init();

	// 背景生成
	backGround_ = std::make_unique<BackGround>();
	backGround_->Init();
	backGround_->SetResource("backGround01");
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
	backGround_->Draw();
	stage_->Draw();
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

const std::vector<Vector2F> StageManager::GetMapChipIndexPositions(const int index)
{
	return stage_->GetMapChipIndexPositions(index);
}

void StageManager::DebugDraw()
{
	stage_->DebugDraw();
	for (const auto& gim : gimmick_)
	{
		gim->DebugDraw();
	}
}

void StageManager::AddGimmick(CharacterBase& _chara, const int _boxNum)
{
	//AvilityBox::Parameter avParam = {};
	//avParam.hitBoxSize = Vector2(48, 48);
	//avParam.gravityPower = 0.5f;
	//avParam.weight = 1.0f;
	//avParam.blastTime = 3.0f;
	//avParam.boxNum = _boxNum;

	////ローカル座標をJsonで読み込み、プレイヤーの向きによって設置場所を変える
	//Vector2F localPos = { 50.0f,50.0f };
	//const bool charaDir = _chara.GetParameter()->direction;
	//const Vector2F charaPos = _chara.GetParameter()->pos;

	//avParam.placePos= charaDir ? Vector2F::SubVector2F(charaPos, localPos) : Vector2F::AddVector2F(charaPos, localPos);
	//std::vector<std::string> componentNameList = { "gravity","move" };

	////いったんアビリティボックスのみ対応
	//std::unique_ptr avBox = std::make_unique<AvilityBox>(avParam, _chara, componentNameList);
	//avBox->Init();
	//gimmick_.push_back(std::move(avBox));
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