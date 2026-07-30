#include "../Application.h"
#include "../Manager/Common/FontManager.h"
#include "../Manager/Common/SpriteEffectManager.h"
#include "../Manager/Common/ScoreManager.h"
#include "../Manager/Common/SoundManager.h"
#include "../Manager/Common/SceneManager.h"
#include "../Manager/Common/Camera.h"
#include "../Manager/Common/ResourceManager.h"
#include "../Manager/Game/GameManager.h"
#include "../Manager/Game/PlayerManager.h"
#include "../Manager/Game/CollisionManager.h"
#include "../Manager/Game/GimmickManager.h"
#include "../Manager/Game/EnemyManager.h"
#include "../Manager/Game/StageManager.h"
#include "../Manager/Game/ItemManager.h"
#include "../Manager/Game/UiManager.h"
#include "../Manager/Game/EventManager.h"
#include "../Factory/FactoryComponent.h"
#include "../Utility/UtilityCommon.h"
#include "../Component/ComponentTextAnimation.h"
#include "SceneTutorial.h"

SceneTutorial::SceneTutorial()
{	
	// 処理の登録
	updataFunc_ = std::bind(&SceneTutorial::LoadingUpdate, this);
	drawFunc_ = std::bind(&SceneTutorial::LoadingDraw, this);
	changeStepMap_.emplace(STEP::GREETING, std::bind(&SceneTutorial::ChangeStepGreeting, this));
	changeStepMap_.emplace(STEP::BASE_ACTION, std::bind(&SceneTutorial::ChangeStepBaseAction, this));
	changeStepMap_.emplace(STEP::ATTACK_ACTION_READY, std::bind(&SceneTutorial::ChangeStepAttackActionReady, this));
	changeStepMap_.emplace(STEP::ATTACK_ACTION, std::bind(&SceneTutorial::ChangeStepAttackAction, this));
	changeStepMap_.emplace(STEP::WORK_ACTION_READY, std::bind(&SceneTutorial::ChangeStepWorkActionReady, this));
	changeStepMap_.emplace(STEP::WORK_ACTION, std::bind(&SceneTutorial::ChangeStepWorkAction, this));
	changeStepMap_.emplace(STEP::ABILITY_GET_ACTION_READY, std::bind(&SceneTutorial::ChangeStepAbilityGetActionReady, this));
	changeStepMap_.emplace(STEP::STAMP_READY, std::bind(&SceneTutorial::ChangeStepStampReady, this));
	changeStepMap_.emplace(STEP::STAMP, std::bind(&SceneTutorial::ChangeStepStamp, this));
	changeStepMap_.emplace(STEP::SHOT_READY, std::bind(&SceneTutorial::ChangeStepShotReady, this));
	changeStepMap_.emplace(STEP::SHOT, std::bind(&SceneTutorial::ChangeStepShot, this));
	changeStepMap_.emplace(STEP::TEREPORT_READY, std::bind(&SceneTutorial::ChangeStepTeleportReady, this));
	changeStepMap_.emplace(STEP::TEREPORT, std::bind(&SceneTutorial::ChangeStepTeleport, this));
	changeStepMap_.emplace(STEP::GRAVITY_READY, std::bind(&SceneTutorial::ChangeStepGravityControllReady, this));
	changeStepMap_.emplace(STEP::GRAVITY, std::bind(&SceneTutorial::ChangeStepGravityControll, this));
	changeStepMap_.emplace(STEP::END, std::bind(&SceneTutorial::ChangeStepEnd, this));

	// 初期化
	messageCnt_ = -1;
	backPosX_ = 0.0f;
	movedAmount_ = 0.0f;
	timer_ = 0.0f;
	isJump_ = false;
	isClear_ = false;
	nowStep_ = STEP::MAX;
	nextStep_ = STEP::MAX;
	soundType_ = SoundType::BGM::MAX;
}

SceneTutorial::~SceneTutorial()
{
}

void SceneTutorial::Init()
{	
	auto& coll = CollisionManager::GetInstance();

	// 乗客室の生成
	stageMng_.Create(StageManager::TYPE::TUTORIAL);

	// カメラ設定
	mainCamera.ChangeMode(Camera::MODE::FIXED_POINT);
	mainCamera.SetCameraPos(Vector2F(0.0f, 0.0f));

	// 基底クラスの初期化処理
	SceneBase::Init();

	// プレイヤーの初期位置を決定
	playerMng_.SetFirstPositions(stageMng_.GetPlayerFirstPositions());

	// サウンド再生
	soundType_ = SoundType::GetRandomGameBgm();
	sndMng_.PlayBgm(soundType_);

	// UI作成
	uiMng_.CreateGameUi();

	// テキスト生成
	message_.fontHandle = fontMng_.CreateMyFont(resMng_.GetFontName("fontKinkakuji"), 48, 5);
	message_.pos = { Application::SCREEN_HALF_X, 655 };
	message_.string = TEXT_MAP[STEP::GREETING].front();
	message_.color = UtilityCommon::WHITE;
	textAnimation_ = std::make_unique<ComponentTextAnimation>(message_, 0.05f);
	textAnimation_->Init();

	// 初期ステップ
	ChangeStep(STEP::GREETING);
	nextStep_ = STEP::BASE_ACTION;
}

void SceneTutorial::NormalUpdate()
{
	SceneBase::NormalUpdate();
	SceneBase::Sweep();

	stepFunction_();

	// テキストアニメーションの更新
	textAnimation_->Update();
}

void SceneTutorial::NormalDraw()
{
	SceneBase::NormalDraw();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	DrawBox(0, 640, Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, UtilityCommon::BLACK, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	textAnimation_->Draw();
}

void SceneTutorial::UpdateMessage()
{	
	// アニメーションを終えている場合
	if (textAnimation_->IsEnd())
	{
		timer_ += scnMng_.GetDeltaTime();

		// まだ数秒表示させるためタイマーの更新
		if (DISPLAY_TIME < timer_)
		{
			// テキストのカウントを更新
			messageCnt_++;

			// テキストがまだ残っている場合
			if (messageCnt_ < static_cast<int>(TEXT_MAP.at(nowStep_).size()))
			{
				// 次のテキストに変更
				message_.string = TEXT_MAP.at(nowStep_)[messageCnt_];

				// テキストアニメーションの再設定
				textAnimation_->SetCharacterString(message_);

				// タイマーの初期化
				timer_ = 0.0f;
			}
			else
			{
				if (nextStep_ == STEP::MAX) { return; }
				messageCnt_ = 0;

				// 次のテキストに変更
				message_.string = TEXT_MAP.at(nextStep_)[messageCnt_];

				// テキストアニメーションの再設定
				textAnimation_->SetCharacterString(message_);

				// 状態変更
				ChangeStep(nextStep_);
			}
		}
	}
}

void SceneTutorial::UpdateStepBaseAction()
{
	if (isClear_)
	{		
		// 条件クリアなので一定時間待つ
		timer_ += scnMng_.GetDeltaTime();
		if (DISPLAY_TIME < timer_)
		{
			// 状態遷移
			ChangeStep(STEP::ATTACK_ACTION_READY);
			nextStep_ = STEP::ATTACK_ACTION;

			// 次のテキストに変更
			message_.string = TEXT_MAP.at(nowStep_)[messageCnt_];

			// テキストアニメーションの再設定
			textAnimation_->SetCharacterString(message_);
		}
		return;
	}

	// ジャンプができたか判定
	if (!isJump_)
	{
		isJump_ = playerMng_.IsJumpPlayer();
	}

	// 移動量の取得
	Vector2F pos = playerMng_.GetPlayersPos().front();
	movedAmount_ += abs(backPosX_ - pos.x);

	// 移動量を確認して移動ができているか判定
	if (movedAmount_ > MOVE_AMOUNT && isJump_)
	{
		// クリア判定
		isClear_ = true;

		// メッセージの更新
		messageCnt_++;

		// 次のテキストに変更
		message_.string = TEXT_MAP.at(nowStep_)[messageCnt_];

		// テキストアニメーションの再設定
		textAnimation_->SetCharacterString(message_);

		// 成功音を鳴らす
		sndMng_.PlaySe(SoundType::SE::SUCCESS);
	}
}

void SceneTutorial::UpdateStepAttackAction()
{
	if (isClear_)
	{
		// 条件クリアなので一定時間待つ
		timer_ += scnMng_.GetDeltaTime();
		if (DISPLAY_TIME < timer_)
		{
			// 状態遷移
			ChangeStep(STEP::WORK_ACTION_READY);
			nextStep_ = STEP::WORK_ACTION;

			// 次のテキストに変更
			message_.string = TEXT_MAP.at(nowStep_)[messageCnt_];

			// テキストアニメーションの再設定
			textAnimation_->SetCharacterString(message_);
		}
		return;
	}

	// 敵が倒せたか判定
	if (enemyMng_.IsBossDestroy(EnemyTypes::TYPE::SLIME))
	{
		// クリア判定
		isClear_ = true;

		// メッセージの更新
		messageCnt_++;

		// 次のテキストに変更
		message_.string = TEXT_MAP.at(nowStep_)[messageCnt_];

		// テキストアニメーションの再設定
		textAnimation_->SetCharacterString(message_);

		// 成功音を鳴らす
		sndMng_.PlaySe(SoundType::SE::SUCCESS);
	}
}

void SceneTutorial::UpdateStepWorkAction()
{
	if (isClear_)
	{
		// 条件クリアなので一定時間待つ
		timer_ += scnMng_.GetDeltaTime();
		if (DISPLAY_TIME < timer_)
		{
			// 状態遷移
			ChangeStep(STEP::ABILITY_GET_ACTION_READY);
			nextStep_ = STEP::STAMP_READY;

			// 次のテキストに変更
			message_.string = TEXT_MAP.at(nowStep_)[messageCnt_];

			// テキストアニメーションの再設定
			textAnimation_->SetCharacterString(message_);
		}
		return;
	}
	else if(scoreManager_.GetScore() >= CLEAR_SCORE)
	{
		// クリア判定
		isClear_ = true;

		// メッセージの更新
		messageCnt_++;

		// 次のテキストに変更
		message_.string = TEXT_MAP.at(nowStep_)[messageCnt_];

		// テキストアニメーションの再設定
		textAnimation_->SetCharacterString(message_);

		// 成功音を鳴らす
		sndMng_.PlaySe(SoundType::SE::SUCCESS);
	}
}

void SceneTutorial::UpdateStepAbilityGetAction()
{
	UpdateMessage();
}

void SceneTutorial::UpdateStepStamp()
{
	if (isClear_)
	{
		// 条件クリアなので一定時間待つ
		timer_ += scnMng_.GetDeltaTime();
		if (DISPLAY_TIME < timer_)
		{
			// 状態遷移
			ChangeStep(STEP::SHOT_READY);
			nextStep_ = STEP::SHOT;

			// 次のテキストに変更
			message_.string = TEXT_MAP.at(nowStep_)[messageCnt_];

			// テキストアニメーションの再設定
			textAnimation_->SetCharacterString(message_);
		}
		return;
	}
	
	itemMng_.CheckTutorialAbilityItem(AvilityTypes::TYPE::STAMP, Vector2F((float)Application::SCREEN_HALF_X, 500.0f));

	if (playerMng_.IsAbilityTutorialClear(AvilityTypes::TYPE::STAMP))
	{
		// クリア判定
		isClear_ = true;

		// メッセージの更新
		messageCnt_++;

		// 次のテキストに変更
		message_.string = TEXT_MAP.at(nowStep_)[messageCnt_];

		// テキストアニメーションの再設定
		textAnimation_->SetCharacterString(message_);

		// 成功音を鳴らす
		sndMng_.PlaySe(SoundType::SE::SUCCESS);

		// アイテム削除
		itemMng_.Clear();
	}
}

void SceneTutorial::UpdateStepShot()
{
	if (isClear_)
	{
		// 条件クリアなので一定時間待つ
		timer_ += scnMng_.GetDeltaTime();
		if (DISPLAY_TIME < timer_)
		{
			// 状態遷移
			ChangeStep(STEP::TEREPORT_READY);
			nextStep_ = STEP::TEREPORT;

			// 次のテキストに変更
			message_.string = TEXT_MAP.at(nowStep_)[messageCnt_];

			// テキストアニメーションの再設定
			textAnimation_->SetCharacterString(message_);
		}
		return;
	}

	itemMng_.CheckTutorialAbilityItem(AvilityTypes::TYPE::SHOT, Vector2F((float)Application::SCREEN_HALF_X, 500.0f));

	if (playerMng_.IsAbilityTutorialClear(AvilityTypes::TYPE::SHOT))
	{
		// クリア判定
		isClear_ = true;

		// メッセージの更新
		messageCnt_++;

		// 次のテキストに変更
		message_.string = TEXT_MAP.at(nowStep_)[messageCnt_];

		// テキストアニメーションの再設定
		textAnimation_->SetCharacterString(message_);

		// 成功音を鳴らす
		sndMng_.PlaySe(SoundType::SE::SUCCESS);

		// アイテム削除
		itemMng_.Clear();
	}
}

void SceneTutorial::UpdateStepTeleport()
{
	if (isClear_)
	{
		// 条件クリアなので一定時間待つ
		timer_ += scnMng_.GetDeltaTime();
		if (DISPLAY_TIME < timer_)
		{
			// 状態遷移
			ChangeStep(STEP::GRAVITY_READY);
			nextStep_ = STEP::GRAVITY;

			// 次のテキストに変更
			message_.string = TEXT_MAP.at(nowStep_)[messageCnt_];

			// テキストアニメーションの再設定
			textAnimation_->SetCharacterString(message_);
		}
		return;
	}

	itemMng_.CheckTutorialAbilityItem(AvilityTypes::TYPE::TELEPORT, Vector2F((float)Application::SCREEN_HALF_X, 500.0f));

	if (playerMng_.IsAbilityTutorialClear(AvilityTypes::TYPE::TELEPORT))
	{
		// クリア判定
		isClear_ = true;

		// メッセージの更新
		messageCnt_++;

		// 次のテキストに変更
		message_.string = TEXT_MAP.at(nowStep_)[messageCnt_];

		// テキストアニメーションの再設定
		textAnimation_->SetCharacterString(message_);

		// 成功音を鳴らす
		sndMng_.PlaySe(SoundType::SE::SUCCESS);

		// アイテム削除
		itemMng_.Clear();
	}
}

void SceneTutorial::UpdateStepGravityControll()
{
	if (isClear_)
	{
		// 条件クリアなので一定時間待つ
		timer_ += scnMng_.GetDeltaTime();
		if (DISPLAY_TIME < timer_)
		{
			// 状態遷移
			ChangeStep(STEP::END);
			nextStep_ = STEP::MAX;

			// 次のテキストに変更
			message_.string = TEXT_MAP.at(nowStep_)[messageCnt_];

			// テキストアニメーションの再設定
			textAnimation_->SetCharacterString(message_);
		}
		return;
	}

	itemMng_.CheckTutorialAbilityItem(AvilityTypes::TYPE::GRAVITYCONTROLL, Vector2F((float)Application::SCREEN_HALF_X, 500.0f));

	if (playerMng_.IsAbilityTutorialClear(AvilityTypes::TYPE::GRAVITYCONTROLL))
	{
		// クリア判定
		isClear_ = true;

		// メッセージの更新
		messageCnt_++;

		// 次のテキストに変更
		message_.string = TEXT_MAP.at(nowStep_)[messageCnt_];

		// テキストアニメーションの再設定
		textAnimation_->SetCharacterString(message_);

		// 成功音を鳴らす
		sndMng_.PlaySe(SoundType::SE::SUCCESS);

		// アイテム削除
		itemMng_.Clear();
	}
}

void SceneTutorial::UpdateStepEnd()
{
	UpdateMessage();

	if (messageCnt_ >= static_cast<int>(TEXT_MAP.at(nowStep_).size()))
	{
		// タイトルシーンに戻る
		scnMng_.ChangeScene(SceneManager::SCENE_ID::TITLE);
		sndMng_.StopBgm(soundType_);
		playerMng_.AllDetachItem();
		itemMng_.SetAllIsCarry(false);
	}
}

void SceneTutorial::ChangeStep(const STEP step)
{
	messageCnt_ = 0;
	timer_ = 0.0f;
	isClear_ = false;
	nowStep_ = step;
	changeStepMap_[nowStep_]();
}

void SceneTutorial::ChangeStepGreeting()
{
	// 状態変更
	stepFunction_ = std::bind(&SceneTutorial::UpdateMessage, this);

	// 次のテキストに変更
	message_.string = TEXT_MAP.at(nowStep_)[messageCnt_];

	// テキストアニメーションの再設定
	textAnimation_->SetCharacterString(message_);
}

void SceneTutorial::ChangeStepBaseAction()
{
	stepFunction_ = std::bind(&SceneTutorial::UpdateStepBaseAction, this);
	backPosX_ = playerMng_.GetPlayersPos().front().x;
	movedAmount_ = 0.0f;
}

void SceneTutorial::ChangeStepAttackActionReady()
{
	stepFunction_ = std::bind(&SceneTutorial::UpdateMessage, this);
}

void SceneTutorial::ChangeStepAttackAction()
{
	stepFunction_ = std::bind(&SceneTutorial::UpdateStepAttackAction, this);

	// 敵生成
	enemyMng_.CreateTutorialEnemy(Vector2F(850, 600));
}

void SceneTutorial::ChangeStepWorkActionReady()
{
	stepFunction_ = std::bind(&SceneTutorial::UpdateMessage, this);
}

void SceneTutorial::ChangeStepWorkAction()
{
	stepFunction_ = std::bind(&SceneTutorial::UpdateStepWorkAction, this);

	// 電車生成
	gimmickMng_.CreateTutorialTrain();

	// お宝を生成
	Vector2F pos = { 500, 500 };
	itemMng_.CreateTreasureItem(ItemTypes::TREASURE_TYPE::TIN_ROBOT, pos);
	pos.x += 200;
	itemMng_.CreateTreasureItem(ItemTypes::TREASURE_TYPE::POT, pos);
	pos.x += 200;
	itemMng_.CreateTreasureItem(ItemTypes::TREASURE_TYPE::STUFFED_TOY, pos);
	pos.x += 200;
	itemMng_.CreateTreasureItem(ItemTypes::TREASURE_TYPE::BOTTLE_SHIP, pos);
}

void SceneTutorial::ChangeStepAbilityGetActionReady()
{
	stepFunction_ = std::bind(&SceneTutorial::UpdateMessage, this);
}

void SceneTutorial::ChangeStepStampReady()
{
	stepFunction_ = std::bind(&SceneTutorial::UpdateMessage, this);
	nextStep_ = STEP::STAMP;
}

void SceneTutorial::ChangeStepStamp()
{
	stepFunction_ = std::bind(&SceneTutorial::UpdateStepStamp, this);
}

void SceneTutorial::ChangeStepShotReady()
{
	stepFunction_ = std::bind(&SceneTutorial::UpdateMessage, this);
}

void SceneTutorial::ChangeStepShot()
{
	stepFunction_ = std::bind(&SceneTutorial::UpdateStepShot, this);
}

void SceneTutorial::ChangeStepTeleportReady()
{
	stepFunction_ = std::bind(&SceneTutorial::UpdateMessage, this);
}

void SceneTutorial::ChangeStepTeleport()
{
	stepFunction_ = std::bind(&SceneTutorial::UpdateStepTeleport, this);
}

void SceneTutorial::ChangeStepGravityControllReady()
{
	stepFunction_ = std::bind(&SceneTutorial::UpdateMessage, this);
}

void SceneTutorial::ChangeStepGravityControll()
{
	stepFunction_ = std::bind(&SceneTutorial::UpdateStepGravityControll, this);
}

void SceneTutorial::ChangeStepEnd()
{
	stepFunction_ = std::bind(&SceneTutorial::UpdateStepEnd, this);
	nextStep_ = STEP::MAX;
}
