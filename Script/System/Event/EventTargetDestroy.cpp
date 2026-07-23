#include <DxLib.h>
#include <cassert>
#include "../../Application.h"
#include "../../Manager/Common/SceneManager.h"
#include "../../Manager/Common/Camera.h"
#include "../../Manager/Game/GimmickManager.h"
#include "../../Object/Gimmick/GimmickTarget.h"
#include "EventTargetDestroy.h"

EventTargetDestroy::EventTargetDestroy(std::unique_ptr<ParameterEventTargetDestroy> parameter) :
	EventBase(std::move(parameter))
{
	parameterPtr_ = dynamic_cast<ParameterEventTargetDestroy*>(GetParameterEventPtr());
	assert(parameterPtr_ != nullptr);
	eventType_ = EventTypes::TYPE::TARGET_DESTROY;
}

EventTargetDestroy::~EventTargetDestroy()
{
}

void EventTargetDestroy::CreateTargets()
{
	// ランダムで生成方法の設定
	TARGET_CREATE_PATTERN type = static_cast<TARGET_CREATE_PATTERN>(GetRand(TARGET_CREATE_PATTERN_MAX - 1));

	// ターゲットの生成
	switch (type)
	{
	case TARGET_CREATE_PATTERN::RANDOM:
		CreateTargetRandom();
		break;

	case TARGET_CREATE_PATTERN::FIX_MOVE:
		CreateTargetFixMove();
		break;

	case TARGET_CREATE_PATTERN::RANDOM_MOVE:
		CreateTargetRandomMove();
		break;
	}
}

void EventTargetDestroy::CreateTargetFix()
{
}

void EventTargetDestroy::CreateTargetFixMove()
{
	// 生成数をランダムで決定
	constexpr int CREATE_NUM = 5;
	constexpr int OFFSET_Y = 100;
	constexpr int FIRST_POS_Y = 160;
	Vector2F cameraPosF = mainCamera.GetPos();	// カメラ位置
	Vector2 cameraPos = cameraPosF.ToVector2();	// カメラ変換
	Vector2F dir = { 1.0f, 0.0f };				// 移動方向
	Vector2 pos = {								// 生成位置
		Application::SCREEN_HALF_X - cameraPos.x,
		FIRST_POS_Y - cameraPos.y
	};

	// 初期方向をランダムで決定
	dir.x = GetRand(1) == 0 ? -1.0f : 1.0f;

	// 生成
	for (int i = 0; i < CREATE_NUM; i++)
	{
		// 反転
		dir.x *= -1.0f;
		
		// ギミック生成
		GimmickManager::CreateParameter createParameter = {};
		createParameter.type = GimmickTypes::TYPE::TARGET;
		createParameter.pos = pos.ToVector2F();
		createParameter.moveDir = dir;
		gimmickManager_.Create(createParameter);

		// 次回用に座標をずらす
		pos.y += OFFSET_Y;
	}
}

void EventTargetDestroy::CreateTargetRandom()
{
	// 生成数をランダムで決定
	int createNum = GetRand(parameterPtr_->targetMax_ - parameterPtr_->targetMin_) + parameterPtr_->targetMin_;
	Vector2F cameraPosF = mainCamera.GetPos();	// カメラ位置
	Vector2 cameraPos = cameraPosF.ToVector2();

	for (int i = 0; i < createNum; i++)
	{
		// ランダム位置にターゲットを生成
		Vector2 pos = {
			GetRand(Application::SCREEN_SIZE_X - parameterPtr_->createRangeOffset_.x * 2) + parameterPtr_->createRangeOffset_.x - cameraPos.x,
			GetRand(Application::SCREEN_SIZE_Y - parameterPtr_->createRangeOffset_.y * 2) + parameterPtr_->createRangeOffset_.y - cameraPos.y
		};

		// ギミック管理に格納
		// ギミック生成
		GimmickManager::CreateParameter createParameter = {};
		createParameter.type = GimmickTypes::TYPE::TARGET;
		createParameter.pos = pos.ToVector2F();
		gimmickManager_.Create(createParameter);
	}
}

void EventTargetDestroy::CreateTargetRandomMove()
{
	// 生成数をランダムで決定
	int createNum = GetRand(parameterPtr_->targetMax_ - parameterPtr_->targetMin_) + parameterPtr_->targetMin_;
	Vector2F cameraPosF = mainCamera.GetPos();	// カメラ位置
	Vector2 cameraPos = cameraPosF.ToVector2();

	for (int i = 0; i < createNum; i++)
	{
		// ランダム位置にターゲットを生成
		Vector2 pos = {
			GetRand(Application::SCREEN_SIZE_X - parameterPtr_->createRangeOffset_.x * 2) + parameterPtr_->createRangeOffset_.x - cameraPos.x,
			GetRand(Application::SCREEN_SIZE_Y - parameterPtr_->createRangeOffset_.y * 2) + parameterPtr_->createRangeOffset_.y - cameraPos.y
		};

		// 移動方向をランダム決定
		Vector2F dir = {
			static_cast<float>(GetRand(100)) / 100.0f,
			static_cast<float>(GetRand(100)) / 100.0f
		};

		// ギミック管理に格納		// ギミック生成
		GimmickManager::CreateParameter createParameter = {};
		createParameter.type = GimmickTypes::TYPE::TARGET;
		createParameter.pos = pos.ToVector2F();
		createParameter.moveDir = dir;
		gimmickManager_.Create(createParameter);
	}
}

void EventTargetDestroy::UpdateChallenge()
{
	// ターゲットをすべて破壊できた場合
	if (gimmickManager_.IsDestrolyAllTarget())
	{
		// 宝箱出現		
		GimmickManager::CreateParameter createParameter = {};
		createParameter.type = GimmickTypes::TYPE::TREASURE_CHEST;
		createParameter.pos = triggerPos_;
		gimmickManager_.Create(createParameter);

		// 時間制限を0にする
		timeLimit_ = 0.0f;
	}

	// 制限時間処理
	timeLimit_ -= sceneManager_.GetDeltaTime();
	if (timeLimit_ <= 0)
	{
		// 残っているターゲットをすべて破壊
		gimmickManager_.AllDeleteTarget();

		// 状態遷移
		ChangeState(STATE::END);
	}
}

void EventTargetDestroy::UpdateEnd()
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

void EventTargetDestroy::ChangeStateChallenge()
{
	// 基底クラスの処理
	EventBase::ChangeStateChallenge();	
	
	// 制限時間の設定
	timeLimit_ = parameterPtr_->challengeTime_;

	// UIの作成
	CreateUi();

	// ターゲットの生成
	CreateTargets();

	// カメラの停止
	CameraStop();
}

void EventTargetDestroy::ChangeStateEnd()
{
	// 基底クラスの処理
	EventBase::ChangeStateEnd();

	// 制限時間の設定
	timeLimit_ = parameterPtr_->endTime_;

	isDeleteUi_ = true;
}