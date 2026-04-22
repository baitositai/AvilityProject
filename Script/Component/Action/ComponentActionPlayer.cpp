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
	isGround_ = false;
}

ComponentActionPlayer::~ComponentActionPlayer()
{
}

void ComponentActionPlayer::Update()
{
	// 移動量の初期化
	moveAmount_ = {};

	// 現在の地面判定取得
	isGround_ = owner_.IsGround();

	// 移動の入力処理
	ProcessInputMove();

	// ジャンプの入力処理
	ProcessInputJump();

	// ジャンプ処理
	Jump();

	// 情報の更新
	owner_.SetMoveAmount(moveAmount_);
	owner_.SetIsGround(isGround_);
}

void ComponentActionPlayer::ProcessInputMove()
{
	// ダッシュの入力判定に応じて速度を変更
	const float moveSpeed = inputManager_.IsNew(InputManager::TYPE::PLAYER_DASH) ? owner_.GetDashSpeed() : owner_.GetParameter()->moveSpeed;

	// 左右移動
	if (inputManager_.IsNew(InputManager::TYPE::PLAYER_MOVE_RIGHT))
	{
		moveAmount_.x = moveSpeed;
		owner_.SetDirection(false);
	}
	else if (inputManager_.IsNew(InputManager::TYPE::PLAYER_MOVE_LEFT))
	{
		moveAmount_.x = - moveSpeed;
		owner_.SetDirection(true);
	}

	// 地面にいる場合
	if (isGround_)
	{
		// 移動量がある場合
		if (moveAmount_.x > 0.0f || moveAmount_.x < 0.0f)
		{
			// 走るアニメーションの変更
			owner_.ChangeAnimation(Player::ANIMATION::WALK);
		}
		else
		{
			// 待機のアニメーションに変更
			owner_.ChangeAnimation(Player::ANIMATION::IDLE);
		}
	}
}

void ComponentActionPlayer::ProcessInputJump()
{
	// 地面にいる場合
	if (isGround_)
	{
		// 初期化
		velocityY_ = 0.0f;

		// 入力判定
		if (inputManager_.IsTrgDown(InputManager::TYPE::PLAYER_JUMP))
		{
			// 地面判定を無効にする
			isGround_ = false;

			// ジャンプ力設定
			velocityY_ = -owner_.GetJumpPow();

			// アニメーションを変更
			owner_.ChangeAnimation(Player::ANIMATION::JUMP);
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

		// 移動量が下方向でかつ地面についてない場合
		if (moveAmount_.y > 0.0f && !isGround_)
		{
			// アニメーションを落下に変更
			owner_.ChangeAnimation(Player::ANIMATION::FALL);
		}
	}
}
