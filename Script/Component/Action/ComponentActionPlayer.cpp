#include "../../Common/Vector2F.h"
#include "../../Manager/Common/InputManager.h"
#include "../../Object/Character/Player.h"
#include "ComponentActionPlayer.h"

ComponentActionPlayer::ComponentActionPlayer(Player& owner) :
	ComponentActionBase(owner),
	owner_(owner),
	inputManager_(InputManager::GetInstance())
{
	velocityY_ = 0.0f;
}

ComponentActionPlayer::~ComponentActionPlayer()
{
}

void ComponentActionPlayer::Update()
{
	// 移動量の取得
	moveAmount_ = {};

	// 移動の入力処理
	ProcessInputMove();

	// ジャンプの入力処理
	ProcessInputJump();

	// ジャンプ処理
	Jump();

	// 移動量の更新
	owner_.SetMoveAmount(moveAmount_);
}

void ComponentActionPlayer::ProcessInputMove()
{
	// ダッシュの入力判定に応じて速度を変更
	const float moveSpeed = inputManager_.IsNew(InputManager::TYPE::PLAYER_DASH) ? owner_.GetDashSpeed() : owner_.GetParameter()->moveSpeed;

	// 左右移動
	if (inputManager_.IsNew(InputManager::TYPE::PLAYER_MOVE_RIGHT))
	{
		moveAmount_.x = moveSpeed;
	}
	else if (inputManager_.IsNew(InputManager::TYPE::PLAYER_MOVE_LEFT))
	{
		moveAmount_.x = - moveSpeed;
	}
	else if (inputManager_.IsNew(InputManager::TYPE::PLAYER_MOVE_UP))
	{
		moveAmount_.y = - moveSpeed;
	}
	else if (inputManager_.IsNew(InputManager::TYPE::PLAYER_MOVE_DOWN))
	{
		moveAmount_.y = + moveSpeed;
	}
}

void ComponentActionPlayer::ProcessInputJump()
{
	// 地面にいる場合
	if (owner_.IsGround())
	{
		// 初期化
		velocityY_ = 0.0f;

		// 入力判定
		if (inputManager_.IsTrgDown(InputManager::TYPE::PLAYER_JUMP))
		{
			// 地面判定を無効にする
			owner_.SetIsGround(false);

			// ジャンプ力設定
			velocityY_ = -owner_.GetJumpPow();
		}
	}
}

void ComponentActionPlayer::Jump()
{
	// 現在の縦の移動量
	float currentY = owner_.GetParameter()->moveAmount.y;

	// ジャンプ力がある場合
	if (velocityY_ < 0.0f)
	{
		// 移動量に追加
		moveAmount_.y = velocityY_;

		// 初期化
		velocityY_ = 0.0f;
	}
	else
	{
		// 現在の移動量を保持
		moveAmount_.y = currentY;
	}
}
