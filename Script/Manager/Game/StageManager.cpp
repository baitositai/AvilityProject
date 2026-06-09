#include <algorithm>
#include "../../Application.h"
#include "../../Utility/UtilityLoad.h"
#include "../../Object/Character/CharacterBase.h"
#include "../../Object/Stage/BackGround.h"
#include "../../Object/Stage/Stage.h"
#include "../../Object/Gimmick/GimmickDoor.h"
#include "../../Object/Gimmick/AvilityBox.h"
#include "../../System/StageGenerator.h"
#include "../Common/Camera.h"
#include "../Common/SceneManager.h"
#include "StageManager.h"

void StageManager::Init()
{
	// 初期化
	if(stage_) stage_->Init();

	// 背景生成
	backGround_ = std::make_unique<BackGround>();
	backGround_->SetResource("backGround02");
	backGround_->Init();
}

void StageManager::Update()
{
	stage_->Update();
}

void StageManager::Draw()
{
	backGround_->Draw();
	stage_->Draw();
}

void StageManager::Create(const TYPE type)
{
	// 種類
	type_ = type;
	
	// 種類別生成処理
	switch (type)
	{
	case TYPE::ROAD:
		CreateStageRoad();
		break;

	default:
		CreateStageRoom();
		break;
	}
}

void StageManager::DebugDraw()
{
	stage_->DebugDraw();
}

const std::vector<Vector2F>& StageManager::GetPlayerFirstPositions() const
{
	return stage_->GetAreaListMap(Stage::LIST_TYPE::PLAYER_FIRST_POS);
}

const std::vector<Vector2F>& StageManager::GetEnemyAreaPositions() const
{
	return stage_->GetAreaListMap(Stage::LIST_TYPE::ENEMY_CREATE_AREA);
}

const Vector2& StageManager::GetStageSize() const
{
	return stage_->GetStageSize();
}

const Vector2F& StageManager::GetBossDoorPos()
{
	return Vector2F::AddVector2F(stage_->GetAreaListMap(Stage::LIST_TYPE::BOSS_DOOR).front(), tileChipSize_.ToVector2F());
}

void StageManager::InitParameter()
{
	// 情報の取得
	const auto jsonParameterMap = UtilityLoad::GetJsonMapArrayData("StageParameter");

	// ロード生成
	const auto jsonRoadParameter = jsonParameterMap.at("road").front();
	auto parameterRoad = std::make_unique<ParameterStage>();
	parameterRoad->LoadParameter(jsonRoadParameter);
	templateParameterMap_.emplace(StageManager::TYPE::ROAD, std::move(parameterRoad));

	// ボス生成
	const auto jsonBossParameter = jsonParameterMap.at("boss").front();
	auto parameterBoss = std::make_unique<ParameterStage>();
	parameterBoss->LoadParameter(jsonBossParameter);
	templateParameterMap_.emplace(StageManager::TYPE::BOSS, std::move(parameterBoss));

	// イベント生成
	const auto jsonEventParameter = jsonParameterMap.at("event").front();
	auto parameterEvent = std::make_unique<ParameterStage>();
	parameterEvent->LoadParameter(jsonBossParameter);
	templateParameterMap_.emplace(StageManager::TYPE::EVENT, std::move(parameterEvent));
}

void StageManager::CreateStageRoad()
{
	// ステージパラメータ取得
	std::unique_ptr<ParameterStage> parameter = std::make_unique<ParameterStage>(std::move(*templateParameterMap_.at(type_)));

	// ステージジェネレーター用のパラメータ設定
	StageGenerator::Parameter generatorParameter = {};
	generatorParameter.connectNum = parameter->connectNum_;
	generatorParameter.candidates = parameter->candidates_;
	auto stageGenerator = std::unique_ptr<StageGenerator>();

	// ステージチップ生成
	parameter->tileIndexs_ = stageGenerator->CreateStageData(generatorParameter);

	// タイルチップサイズを保持
	tileChipSize_ = parameter->chipSize_;

	// ステージ生成
	stage_ = std::make_unique<Stage>(std::move(parameter));
	stage_->Init();
}

void StageManager::CreateStageRoom()
{
	// ステージパラメータ
	std::unique_ptr<ParameterStage> parameter = std::make_unique<ParameterStage>(std::move(*templateParameterMap_.at(type_)));

	// タイルチップサイズを保持
	tileChipSize_ = parameter->chipSize_;

	// タイル配列を設定
	parameter->tileIndexs_ = UtilityLoad::LoadCSVData(parameter->path_);

	// ステージ生成
	stage_ = std::make_unique<Stage>(std::move(parameter));
}

StageManager::StageManager()
{
	type_ = TYPE::NONE;
	InitParameter();
}

StageManager::~StageManager()
{
}