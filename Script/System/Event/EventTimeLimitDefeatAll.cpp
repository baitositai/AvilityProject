#include <DxLib.h>
#include <cassert>
#include "../../Application.h"
#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Game/EventManager.h"
#include "../../Manager/Game/EnemyManager.h"
#include "../../Manager/Game/GimmickManager.h"
#include "EventTimeLimitDefeatAll.h"

EventTimeLimitDefeatAll::EventTimeLimitDefeatAll(std::unique_ptr<ParameterEventTimeLimitDefeatAll> parameter) :
	EventBase(std::move(parameter))
{
	parameterPtr_ = dynamic_cast<ParameterEventTimeLimitDefeatAll*>(GetParameterEventPtr());
	assert(parameterPtr_ != nullptr);

	timeLimit_ = 0.0f;
}

EventTimeLimitDefeatAll::~EventTimeLimitDefeatAll()
{
}

void EventTimeLimitDefeatAll::CreateEnemyList()
{	
	// 固定の場合
	if (GetRand(ENEMY_CREATE_TYPE_MAX - 1) == 0)
	{
		ETYPE type = static_cast<ETYPE>(GetRand(EnemyTypes::MAX - 1));
		int wave = GetRand(parameterPtr_->waveMax_ - parameterPtr_->waveMin_) + parameterPtr_->waveMin_;
		for (int i = 0; i < wave; i++)
		{
			int createNum = GetRand(parameterPtr_->enemyNumMax_ - parameterPtr_->enemyNumMin_) + parameterPtr_->enemyNumMin_;
			std::vector<ETYPE> enemyList;
			for (int j = 0; j < createNum; j++)
			{
				enemyList.push_back(type);
			}
			createEnemiesList_.push_back(enemyList);
		}
	}
	// ランダムの場合
	else
	{
		int wave = GetRand(parameterPtr_->waveMax_ - parameterPtr_->waveMin_) + parameterPtr_->waveMin_;
		for (int i = 0; i < wave; i++)
		{
			int createNum = GetRand(parameterPtr_->enemyNumMax_ - parameterPtr_->enemyNumMin_) + parameterPtr_->enemyNumMin_;
			std::vector<ETYPE> enemyList;
			for (int j = 0; j < createNum; j++)
			{	
				ETYPE type = static_cast<ETYPE>(GetRand(EnemyTypes::MAX - 1));
				enemyList.push_back(type);
			}
			createEnemiesList_.push_back(enemyList);
		}
	}
}

void EventTimeLimitDefeatAll::CreateEnemies()
{
	const Vector2 RIGHT_TOP = { Application::SCREEN_SIZE_X - parameterPtr_->createLeftTopPos_.x - parameterPtr_->createRange_.x, parameterPtr_->createLeftTopPos_.y };	// 右の生成範囲トップ位置
	Vector2 pos = {};	// 生成位置
	bool dir = true;	// 方向
	
	auto& enemyList = createEnemiesList_.front();
	for (auto& type : enemyList)
	{
		// 方向を指定してトップを決定
		const Vector2 top = dir ? parameterPtr_->createLeftTopPos_ : RIGHT_TOP;

		// 生成位置を決定
		pos = {
			top.x + GetRand(parameterPtr_->createRange_.x),
			top.y + GetRand(parameterPtr_->createRange_.y)
		};

		// 敵の生成
		enemyManager_.Create(type, pos.ToVector2F());
	}

	// 先頭要素を消す
	createEnemiesList_.pop_front();
}

void EventTimeLimitDefeatAll::UpdateChallenge()
{
	// イベントで出現した敵が空の場合
	if (enemyManager_.IsEmptyEventEnemies())
	{
		// 敵の生成処理
		CreateEnemies();

		// 生成リストが空の場合
		if (createEnemiesList_.empty())
		{
			// 状態遷移
			ChangeState(STATE::END);
		}
	}

	// 制限時間処理
	timeLimit_ -= sceneManager_.GetDeltaTime();
	if (timeLimit_ <= 0)
	{
		// 状態遷移
		ChangeState(STATE::END);
	}
}

void EventTimeLimitDefeatAll::UpdateEnd()
{
	// 制限時間処理
	timeLimit_ -= sceneManager_.GetDeltaTime();
	if (timeLimit_ <= 0)
	{
		// カメラ再開
		CameraRestart();

		// 削除予定
		isDelete_ = true;
	}
}

void EventTimeLimitDefeatAll::ChangeStateChallenge()
{	
	// 基底クラスの処理
	EventBase::ChangeStateChallenge();

	// カメラ停止
	CameraStop();

	// 敵生成リスト生成
	CreateEnemyList();

	// 時間制限を設ける
	timeLimit_ = parameterPtr_->challengeTime_;
}

void EventTimeLimitDefeatAll::ChangeStateEnd()
{
	// 基底クラスの処理
	EventBase::ChangeStateEnd();

	// 時間制限を設ける
	timeLimit_ = parameterPtr_->endTime_;
}