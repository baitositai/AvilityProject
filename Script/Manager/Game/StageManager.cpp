#include <algorithm>
#include "../../Application.h"
#include "../../Utility/UtilityLoad.h"
#include "../../Object/Character/CharacterBase.h"
#include "../../Object/Stage/BackGround.h"
#include "../../Object/Stage/Stage.h"
#include "../../Object/Stage/StageTrain.h"
#include "../../Object/Gimmick/GimmickDoor.h"
#include "../../System/StageGenerator.h"
#include "../Common/Camera.h"
#include "../Common/SceneManager.h"
#include "StageManager.h"

void StageManager::Init()
{
	// 初期化
	if(stage_) stage_->Init();

	for (auto& back : backGrounds_)
	{
		back->Init();
	}
}

void StageManager::Update()
{
	stage_->Update();
	for (auto& back : backGrounds_)
	{
		back->Update();
	}
}

void StageManager::Draw()
{
	for (auto& back : backGrounds_)
	{
		back->Draw();
	}
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

	case TYPE::TRAIN:
		CreateStageTrain();
		break;

	case TYPE::BOSS:
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

const std::vector<Vector2F>& StageManager::GetEventTriggerPositions() const
{
	return stage_->GetAreaListMap(Stage::LIST_TYPE::EVENT);
}

const std::vector<Vector2F>& StageManager::GetItemCreatePositions() const
{
	return stage_->GetAreaListMap(Stage::LIST_TYPE::ITEM_CREATE_AREA);
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
	const auto& jsonRoadParameter = jsonParameterMap.at("road").front();
	auto parameterRoad = std::make_unique<ParameterStage>();
	parameterRoad->LoadParameter(jsonRoadParameter);
	templateParameterMap_.emplace(StageManager::TYPE::ROAD, std::move(parameterRoad));

	// ボス生成
	const auto&jsonBossParameter = jsonParameterMap.at("boss").front();
	auto parameterBoss = std::make_unique<ParameterStage>();
	parameterBoss->LoadParameter(jsonBossParameter);
	templateParameterMap_.emplace(StageManager::TYPE::BOSS, std::move(parameterBoss));

	// イベント生成
	const auto& jsonEventParameter = jsonParameterMap.at("event").front();
	auto parameterEvent = std::make_unique<ParameterStage>();
	parameterEvent->LoadParameter(jsonBossParameter);
	templateParameterMap_.emplace(StageManager::TYPE::EVENT, std::move(parameterEvent));

	// 車内生成
	const auto& jsonTrainParameter = jsonParameterMap.at("train").front();
	auto parameterTrain = std::make_unique<ParameterStage>();
	parameterTrain->LoadParameter(jsonTrainParameter);
	templateParameterMap_.emplace(StageManager::TYPE::TRAIN, std::move(parameterTrain));
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
	//stage_->Init();

	// 背景生成
	CreateBackGround();

	// 背景のスクロール速度設定
	float addScrollSpeed = -0.05f;
	float scrollSpeed = -Camera::SCROLL_SPEED - addScrollSpeed * static_cast<int>(backGrounds_.size());
	for (auto& back : backGrounds_)
	{
		back->SetScrollSpeed(scrollSpeed);
		scrollSpeed += addScrollSpeed;
	}
}

void StageManager::CreateStageTrain()
{
	// ステージパラメータ
	std::unique_ptr<ParameterStage> parameter = std::make_unique<ParameterStage>(std::move(*templateParameterMap_.at(type_)));

	// タイルチップサイズを保持
	tileChipSize_ = parameter->chipSize_;

	// タイル配列を設定
	parameter->tileIndexs_ = UtilityLoad::LoadCSVData(parameter->path_);

	// ステージ生成
	stage_ = std::make_unique<StageTrain>(std::move(parameter));
	
	// 背景生成
	CreateBackGround();

	// 乗客室の背景を追加
	auto back = std::make_unique<BackGround>();
	back->SetType(BackGround::TYPE::FIX);
	back->SetResource("guestRoom");
	backGrounds_.push_back(std::move(back));

	back = std::make_unique<BackGround>();
	back->SetType(BackGround::TYPE::FIX);
	back->SetResource("guestRoomDeco");
	backGrounds_.push_back(std::move(back));
}

void StageManager::CreateStageRoom()
{
	// 共通処理
	CreateStageCommon();
	CreateBackGround();
}

void StageManager::CreateStageCommon()
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

void StageManager::CreateBackGround()
{	
	// 背景
	constexpr int BACK_GROUND_NUM = 9;
	float scrollSpeed = -0.5f;
	float addScrollSpeed = -0.2f;
	for (int i = 0; i < BACK_GROUND_NUM; i++)
	{
		auto backGround = std::make_unique<BackGround>();
		backGround->SetType(BackGround::TYPE::SCROLL);
		backGround->SetScrollSpeed(scrollSpeed);
		backGround->SetResource("backGround" + std::to_string(i));
		backGrounds_.push_back(std::move(backGround));
		scrollSpeed += addScrollSpeed;
	}
}

StageManager::StageManager()
{
	type_ = TYPE::NONE;
	InitParameter();
}

StageManager::~StageManager()
{
}